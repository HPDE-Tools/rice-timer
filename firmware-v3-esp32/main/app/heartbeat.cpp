// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <charconv>
#include <string_view>

#include "app/heartbeat.hpp"

#include "app/logger_instance.hpp"
#include "common/task.hpp"
#include "device/capture_manager.hpp"
#include "priorities.hpp"

namespace app {

class Heartbeat : public Task {
 public:
  static constexpr char TAG[] = "heartbeat";

  explicit Heartbeat(int32_t period_ms) : Task{}, period_ms_(period_ms) {}

  esp_err_t Start() { return Task::SpawnSame(TAG, 2048, kPriorityBackground); }
  using Task::Kill;

 protected:
  void Run() override {
    static char buf_[] = "h,2147483647,2147483647";
    TickType_t last_wake_tick = xTaskGetTickCount();
    char* const end = buf_ + sizeof(buf_) - 1;
    while (true) {
      const uint32_t capture =
          CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
      const TickType_t uptime_tick = xTaskGetTickCount();
      char* p = buf_ + 2;
      p = std::to_chars(p, end, capture, /*base*/ 10).ptr;
      *p++ = ',';
      p = std::to_chars(p, end, uptime_tick).ptr;
      *p++ = '\0';
      SendToLogger(kHeartbeatProducer, std::string_view(buf_, p - buf_ - 1));
      vTaskDelayUntil(&last_wake_tick, pdMS_TO_TICKS(period_ms_));
    }
  }

 private:
  int32_t period_ms_;
};

std::unique_ptr<Heartbeat> g_heartbeat;

esp_err_t SetupHeartbeat() {
  g_heartbeat = std::make_unique<Heartbeat>(/*period_ms*/ 1000);
  return g_heartbeat ? ESP_OK : ESP_FAIL;
}
esp_err_t StartHeartbeat() { return g_heartbeat->Start(); }
void StopHeartbeat() { g_heartbeat->Kill(); }

}  // namespace app
