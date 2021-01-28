#include "device/gps.hpp"

#include <sys/time.h>
#include <time.h>
#include <cinttypes>
#include <string_view>

#include "driver/uart.h"
#include "fmt/chrono.h"
#include "fmt/compile.h"
#include "fmt/core.h"
#include "minmea.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "common/logging.hpp"
#include "common/scope_guard.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "io/autobaud.hpp"
#include "logger.hpp"
#include "ui/model.hpp"

namespace {

constexpr char TAG[] = "gps";

constexpr uint32_t kGpsDetectTimeoutMs = 10000;
constexpr uint32_t kGpsRetryMs = 1000;
constexpr uint32_t kGpsPollMs = 10;

constexpr size_t kGpsDefaultBaud = 9600;
// accepted actual baud range: [desired - desired / tol, desired + desired / tol]
constexpr int kGpsBaudRelativeTolerance = 30;

constexpr int kGpsStackSize = 6000;

constexpr int kPpsTimeToLiveMs = 500;
constexpr int kMaxAdjustableDeltaTimeSec = 2 * 60 * 60;

}  // namespace

GpsManager::GpsManager(Option option) : option_(option) {
  CHECK(0 <= option.uart_num && option.uart_num < UART_NUM_MAX);
  CHECK(option.uart_dev != nullptr);
  capture_manager_ = CaptureManager::GetInstance(option.pps_capture_unit);
}

esp_err_t GpsManager::Setup() {
  const uart_config_t config{
      .baud_rate = kGpsDefaultBaud,  // this will be detected (autobaud) later
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .rx_flow_ctrl_thresh = 0,
      .source_clk = UART_SCLK_APB,
  };
  TRY(uart_driver_install(
      uart_num(), /*rx buf*/ 1024, /*tx buf*/ 1024, /*queue size*/ 128, &uart_queue_, 0));
  MAKE_SCOPE_EXIT(guard_driver) { uart_driver_delete(uart_num()); };

  TRY(uart_param_config(uart_num(), &config));
  TRY(uart_set_pin(
      uart_num(),
      option_.uart_tx_pin,
      option_.uart_rx_pin,
      UART_PIN_NO_CHANGE,
      UART_PIN_NO_CHANGE));

  line_reader_ = io::UartLineReader::Create(
      uart_num(),
      uart_queue_,
      {
          .delimiter = '\n',
          .repeat = 1,
      });
  if (!line_reader_) {
    return ESP_FAIL;
  }

  TRY(mcpwm_gpio_init(option_.pps_capture_unit, option_.pps_capture_io, option_.pps_pin));
  using namespace std::placeholders;
  TRY(capture_manager_->Subscribe(
      option_.pps_capture_signal,
      MCPWM_POS_EDGE,
      0,
      std::bind(HandlePpsCapture, this, _1, _2, _3, _4)));
  // no need to defer unsubscribe, as this is the last step

  guard_driver.dismiss();
  return ESP_OK;
}

GpsManager::~GpsManager() {
  capture_manager_->Unsubscribe(option_.pps_capture_signal);
  uart_driver_delete(uart_num());
}

esp_err_t GpsManager::Start() {
  TRY(Task::SpawnSame(TAG, kGpsStackSize, option_.priority));
  return ESP_OK;
}

void GpsManager::Stop() { Task::Kill(); }

esp_err_t GpsManager::SendRaw(const std::string_view raw) {
  return uart_write_bytes(uart_num(), raw.data(), raw.size()) == raw.size() ? ESP_OK : ESP_FAIL;
}

esp_err_t GpsManager::SendNmea(const std::string_view payload) {
  uint8_t checksum = 0;
  for (char c : payload) {
    checksum ^= c;
  }
  if (uart_write_bytes(uart_num(), "$", 1) != 1) {
    return ESP_FAIL;
  }
  TRY(SendRaw(payload));
  const std::array suffix{
      '*',
      HexDigitUpper((checksum >> 4) & 0xf),
      HexDigitUpper(checksum & 0xf),
      '\r',
      '\n',
  };
  if (uart_write_bytes(uart_num(), suffix.data(), suffix.size()) != suffix.size()) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

std::string GpsManager::ReadRawLine(TickType_t timeout) {
  return line_reader_->ReadOneLine(timeout);
}

bool GpsManager::CheckIsPpsRecent() {
  if (is_pps_recent_ && static_cast<int32_t>(xTaskGetTickCount() - latest_pps_time_os_) >
                            pdMS_TO_TICKS(kPpsTimeToLiveMs)) {
    is_pps_recent_ = false;
    return false;
  }
  return is_pps_recent_;
}

void GpsManager::Run() {
  line_reader_->DiscardInputBuffer();
  while (true) {
    // poll
    const std::string line = line_reader_->ReadOneLine(pdMS_TO_TICKS(kGpsPollMs));
    const TickType_t line_time_os_tick = xTaskGetTickCount();
    const uint32_t line_time_capture =
        capture_manager_->TriggerNow(option_.software_capture_signal);
    uint32_t pps_time_capture = 0;
    const bool pps_capture_received = (xTaskNotifyWait(0, 0, &pps_time_capture, 0) == pdPASS);

    // process
    if (pps_capture_received) {
      ui::g_model.pps_capture = pps_time_capture;
      SendToLogger(fmt::format("p,{}", pps_time_capture));
    }
    if (!line.empty()) {
      ProcessGpsLine(TrimSuffix(line, "\r\n"), line_time_os_tick, line_time_capture);
    }
  }
}

void GpsManager::HandlePpsCapture(
    GpsManager* self,
    mcpwm_unit_t /*unit*/,
    mcpwm_capture_signal_t /*signal*/,
    uint32_t /*edge*/,
    uint32_t value) {
  self->latest_pps_time_os_ = xTaskGetTickCountFromISR();
  self->latest_pps_time_capture_ = value;
  self->is_pps_recent_ = true;
  if (self->handle()) {
    xTaskNotifyFromISR(self->handle(), value, eSetValueWithOverwrite, nullptr);
  }
}

void GpsManager::ProcessGpsLine(
    std::string_view trimmed_line, TickType_t time_os, uint32_t time_capture) {
  SendToLogger(fmt::format(/*FMT_COMPILE*/ ("g,{},{}"), time_capture, trimmed_line));

  minmea_sentence_rmc gprmc;
  switch (minmea_sentence_id(trimmed_line.data(), true)) {
    case MINMEA_SENTENCE_RMC: {
      if (!minmea_parse_rmc(&gprmc, trimmed_line.data())) {
        ESP_LOGW(TAG, "GPRMC not valid");
        return;
      }
      break;
    }
    default:
      // TODO(summivox): hand it to whoever needs this
      return;
  }

  // TODO(summivox): refactor this out
  ui::g_model.gps = ui::Model::Gps{
      .hour = (uint8_t)gprmc.time.hours,
      .minute = (uint8_t)gprmc.time.minutes,
      .second = (uint8_t)gprmc.time.seconds,
      .millisecond = (uint16_t)(gprmc.time.microseconds / 1000),
      .latitude = minmea_tocoord(&gprmc.latitude),
      .longitude = minmea_tocoord(&gprmc.longitude),
  };

  // if the message is on a whole second, it corresponds to the latest PPS event
  if (gprmc.time.microseconds == 0 && CheckIsPpsRecent()) {
    TimeZulu nmea_zulu = ToZulu(century_, gprmc.date, gprmc.time);
    const TimeUnix nmea_unix = ToUnix(nmea_zulu);
    PpsGpsMatch match{
        .pps_time_os = latest_pps_time_os_,
        .pps_time_capture = latest_pps_time_capture_,
        .gps_time_os = time_os,
        .gps_time_capture = time_capture,
        .gps_nmea_tm = nmea_zulu,
        .gps_nmea_unix = nmea_unix,
    };
    if (option_.adjust_system_time) {
      AdjustSystemTime(match);
    }
    ESP_LOGV(
        TAG,
        "%s",
        fmt::format(
            FMT_COMPILE("match {} {:%F %T} - pps {} {} - gps {} ({:+}) {} ({:+})\n"),
            nmea_unix,
            nmea_zulu,
            match.pps_time_os,
            match.pps_time_capture,
            match.gps_time_os,
            static_cast<int32_t>(match.gps_time_os - match.pps_time_os),
            match.gps_time_capture,
            static_cast<int32_t>(match.gps_time_capture - match.pps_time_capture))
            .c_str());
  }
}

void GpsManager::AdjustSystemTime(const PpsGpsMatch& match) {
  // 1 us => how many capture ticks? (this should only ever need to be set once)
  static const int kCaptureTicksInUs = capture_manager_->GetNominalFreqHz() / 1'000'000;

  TimeUnixWithUs system_now{};
  gettimeofday(&system_now, /*tz*/ nullptr);
  const uint32_t capture_now = capture_manager_->TriggerNow(option_.software_capture_signal);

  // `auto` is used to adapt to whatever type we have in `timeval`
  const auto a_s = system_now.tv_sec;
  const auto a_us = system_now.tv_usec;
  const auto b_s = match.gps_nmea_unix;
  const int32_t b_us =
      static_cast<int32_t>(capture_now - match.pps_time_capture) / kCaptureTicksInUs;
  const auto d_s = b_s - a_s;
  const auto d_us = b_us - a_us;

  ESP_LOGV(
      TAG,
      "sys=%" PRIi64 ".%06" PRIi64 " gps=%" PRIi64 ".%06" PRIi64 " ds=%" PRIi64 " dus=%" PRIi64,
      static_cast<int64_t>(a_s),
      static_cast<int64_t>(a_us),
      static_cast<int64_t>(b_s),
      static_cast<int64_t>(b_us),
      static_cast<int64_t>(d_s),
      static_cast<int64_t>(d_us));

  if (std::abs(d_s) >= kMaxAdjustableDeltaTimeSec) {
    const TimeUnixWithUs nmea_unix{.tv_sec = b_s, .tv_usec = b_us};
    settimeofday(&nmea_unix, /*tz*/ nullptr);
    ESP_LOGW(
        TAG,
        "settimeofday: %" PRIi64 " -> %" PRIi64,
        static_cast<int64_t>(a_s),
        static_cast<int64_t>(b_s));
  } else {
    TimeUnixWithUs delta{.tv_sec = d_s, .tv_usec = d_us};
    adjtime(&delta, /*old_delta*/ nullptr);
  }
}

/////////////////////////////////////////////

esp_err_t MtkDetectAndConfigure(GpsManager* gps, int baud_rate, int output_period_ms) {
  CHECK(gps != nullptr);
  while (true) {
    SCOPE_EXIT { vTaskDelay(pdMS_TO_TICKS(kGpsRetryMs)); };

    ESP_LOGI(TAG, "Detecting baud rate");
    std::optional<int32_t> bit_width =
        io::DetectUartBitWidth(gps->uart_dev(), {.timeout = kGpsDetectTimeoutMs});
    if (!bit_width) {
      ESP_LOGW(TAG, "Baud rate detection fail");
      continue;
    }
    io::SetUartBitWidth(gps->uart_dev(), *bit_width);
    std::optional<uint32_t> current_baud = io::GetCurrentUartBaudRate(gps->uart_num());
    if (!current_baud) {
      ESP_LOGW(TAG, "Failed to get current baud rate");
      continue;
    }
    ESP_LOGI(TAG, "Baud rate set to %" PRIu32, *current_baud);

    if (gps->ReadRawLine(kGpsDetectTimeoutMs).empty()) {
      ESP_LOGW(TAG, "Did not receive line from GPS");
      continue;
    }
    const int tol = baud_rate / kGpsBaudRelativeTolerance;
    if (!(baud_rate - tol <= current_baud && current_baud <= baud_rate + tol)) {
      ESP_LOGI(TAG, "Attempt to change baud to %" PRIu32, baud_rate);
      TRY(gps->SendNmea(fmt::format("PMTK251,{}", baud_rate)));
      continue;
    }

    break;
  }

  // configure output rate and type
  TRY(gps->SendNmea(fmt::format("PMTK220,{}", output_period_ms)));
  TRY(gps->SendNmea("PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"));  // GPRMC
  return ESP_OK;
}
