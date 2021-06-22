// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cinttypes>

#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "app/device_id.hpp"
#include "common/logging.hpp"
#include "math/polyfill.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"

namespace ui {
namespace view {

namespace {
constexpr char TAG[] = "ui/view";

constexpr lv_color_t kOn = LV_COLOR_BLACK;
constexpr lv_color_t kOff = LV_COLOR_WHITE;

template <typename TFloat>
constexpr char SignChar(TFloat t) {
  return t >= 0 ? '+' : '-';
}

}  // namespace

struct Gps {
  lv_obj_t* container;
  lv_obj_t* label_latlong;
  lv_obj_t* label_datetime;

  ~Gps() {
    lv_obj_del(label_datetime);
    lv_obj_del(label_latlong);
    lv_obj_del(container);
  }

  Gps(lv_obj_t* parent) {
    container = lv_cont_create(parent, nullptr);
    lv_obj_set_auto_realign(container, true);
    lv_obj_reset_style_list(container, 0);
    lv_obj_add_style(container, 0, &g_style->container_hr_bottom);
    lv_cont_set_fit2(container, LV_FIT_PARENT, LV_FIT_TIGHT);
    lv_cont_set_layout(container, LV_LAYOUT_ROW_TOP);
    lv_obj_set_style_local_pad_inner(container, 0, LV_STATE_DEFAULT, 6);

    label_latlong = lv_label_create(container, nullptr);
    lv_obj_reset_style_list(label_latlong, 0);
    lv_obj_add_style(label_latlong, 0, &g_style->text_tiny);
    lv_label_set_align(label_latlong, LV_LABEL_ALIGN_RIGHT);

    label_datetime = lv_label_create(container, label_latlong);
  }

  void Render(const std::optional<Model::Gps>& gps) {
    if (gps) {
      lv_label_set_text_fmt(
          label_latlong,
          "%c% 08.5f\n"
          "%c%09.5f",
          SignChar(gps->latitude),
          std::abs(gps->latitude),
          SignChar(gps->longitude),
          std::abs(gps->longitude));

      lv_label_set_text_fmt(
          label_datetime,
          "%04d-%02d-%02d\n"
          "%02d:%02d:%02d.%1d",
          gps->year,
          gps->month,
          gps->day,
          gps->hour,
          gps->minute,
          gps->second,
          gps->millisecond / 100);
    } else {
      lv_label_set_text(
          label_latlong,
          "? --.-----\n"
          "?---.-----");
      lv_label_set_text(
          label_datetime,
          "****-**-**\n"
          "**:**:**.*");
    }
  }
};

struct Imu {
  lv_obj_t* container;
  lv_obj_t* label_acc;
  lv_obj_t* label_gyro;

  ~Imu() {
    lv_obj_del(label_gyro);
    lv_obj_del(label_acc);
    lv_obj_del(container);
  }

  Imu(lv_obj_t* parent) {
    container = lv_cont_create(parent, nullptr);
    lv_obj_set_auto_realign(container, true);
    lv_obj_reset_style_list(container, 0);
    lv_cont_set_fit(container, LV_FIT_TIGHT);
    lv_cont_set_layout(container, LV_LAYOUT_ROW_TOP);
    lv_obj_set_style_local_pad_inner(container, 0, LV_STATE_DEFAULT, 7);

    label_acc = lv_label_create(container, nullptr);
    lv_obj_reset_style_list(label_acc, 0);
    lv_obj_add_style(label_acc, 0, &g_style->text_tiny);

    label_gyro = lv_label_create(container, label_acc);
  }

  void Render(const std::optional<Model::Imu>& imu) {
    if (imu) {
      lv_label_set_text_fmt(
          label_acc,
          "%+5.2f\n"
          "%+5.2f\n"
          "%+5.2f",
          imu->ax_g,
          imu->ay_g,
          imu->az_g);
      lv_label_set_text_fmt(
          label_gyro,
          "%c%03d\n"
          "%c%03d\n"
          "%c%03d",
          SignChar(imu->wx_dps),
          std::abs((int)std::round(imu->wx_dps)),
          SignChar(imu->wy_dps),
          std::abs((int)std::round(imu->wy_dps)),
          SignChar(imu->wz_dps),
          std::abs((int)std::round(imu->wz_dps)));
    } else {
      lv_label_set_text(label_acc, "?-.--\n?-.--\n?-.--");
      lv_label_set_text(label_gyro, "?---\n?---\n?---");
    }
  }
};

struct Throughput {
  static constexpr float kSampleRateHz = 1000 / 50;  // TODO: parameterize
  static constexpr float kDecay = 0.9;               // weight of the latest data
  lv_obj_t* label;

  TickType_t last_time{};
  int last_gps = 0;
  int last_imu = 0;
  int last_can = 0;

  float average_gps = 0;
  float average_imu = 0;
  float average_can = 0;

  ~Throughput() { lv_obj_del(label); }

  Throughput(lv_obj_t* parent) {
    label = lv_label_create(parent, nullptr);
    lv_obj_reset_style_list(label, 0);
    lv_obj_add_style(label, 0, &g_style->text_tiny);

    // reserve some room (saves a container)
    lv_label_set_text(label, "G 0\nI 0\nC 0");
    lv_label_set_long_mode(label, LV_LABEL_LONG_CROP);
    lv_obj_set_width(label, 45);
  }

  void Render(const Model::Counter& counter) {
    const TickType_t now = xTaskGetTickCount();
    const int dt = SignedMinus(now, last_time);
    if (dt < 1000) {
      return;
    }
    last_time = now;
    const int curr_gps = counter.gps.load();
    const int curr_imu = counter.imu.load();
    const int curr_can = counter.can.load();
    const int diff_gps = SignedMinus(curr_gps, last_gps);
    const int diff_imu = SignedMinus(curr_imu, last_imu);
    const int diff_can = SignedMinus(curr_can, last_can);
    const float freq = 1000.0f / dt;
    average_gps = std::lerp(average_gps, diff_gps * freq, kDecay);
    average_imu = std::lerp(average_imu, diff_imu * freq, kDecay);
    average_can = std::lerp(average_can, diff_can * freq, kDecay);
    last_gps = curr_gps;
    last_can = curr_can;
    last_imu = curr_imu;
    lv_label_set_text_fmt(
        label,
        "G %d\n"
        "I %d\n"
        "C %d",
        (int)std::round(average_gps),
        (int)std::round(average_imu),
        (int)std::round(average_can));
  }
};

struct LoggerPath {
  lv_obj_t* label;

  TickType_t last_time{};

  ~LoggerPath() { lv_obj_del(label); }

  LoggerPath(lv_obj_t* parent) {
    label = lv_label_create(parent, nullptr);
    lv_obj_reset_style_list(label, 0);
    lv_obj_add_style(label, 0, &g_style->text_tiny);
    lv_obj_add_style(label, 0, &g_style->container_hr_top);

    // reserve some room (saves a container)
    lv_label_set_text(label, " --- no card ---");
    lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label, 128);
  }

  void Render(const std::optional<Model::Logger>& logger) {
    const TickType_t now = xTaskGetTickCount();
    const int dt = SignedMinus(now, last_time);
    if (dt < 1000) {
      return;
    }
    last_time = now;
    if (logger) {
      lv_label_set_text_fmt(
          label,
          ":%02X%02X/%" PRId64 "/%d:%d",
          app::g_device_mac[4],
          app::g_device_mac[5],
          logger->session_id,
          logger->split_id,
          logger->lines);
    } else {
      lv_label_set_text(label, " --- no card ---");
    }
  }
};

struct Root {
  lv_obj_t* container;

  std::unique_ptr<Gps> gps;
  std::unique_ptr<Imu> imu;
  std::unique_ptr<Throughput> throughput;
  std::unique_ptr<LoggerPath> logger_path;

  ~Root() {
    logger_path.reset();
    throughput.reset();
    imu.reset();
    gps.reset();
    lv_obj_del(container);
  }

  Root(lv_obj_t* parent) {
    container = lv_cont_create(parent, nullptr);
    lv_obj_align(container, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_set_auto_realign(container, true);
    lv_obj_reset_style_list(container, 0);
    lv_cont_set_fit2(container, LV_FIT_MAX, LV_FIT_MAX);
    lv_cont_set_layout(container, LV_LAYOUT_PRETTY_MID);

    gps = std::make_unique<Gps>(container);
    imu = std::make_unique<Imu>(container);
    throughput = std::make_unique<Throughput>(container);
    logger_path = std::make_unique<LoggerPath>(container);
  }

  void Render(const Model& model) {
    gps->Render(model.gps);
    imu->Render(model.imu);
    throughput->Render(model.counter);
    logger_path->Render(model.logger);
  }
};

}  // namespace view
}  // namespace ui
