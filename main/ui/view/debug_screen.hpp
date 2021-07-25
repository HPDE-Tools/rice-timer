// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

#include "device/gps_utils.hpp"

namespace ui {
namespace view {

struct DebugScreen : Screen {
  static constexpr float kDecay = 0.9;  // smoothing weight for latest data

  lv_obj_t* table;

  TickType_t last_time{};

  int last_gps = 0;
  int last_imu = 0;
  int last_can = 0;

  float average_gps = 0;
  float average_imu = 0;
  float average_can = 0;

  virtual ~DebugScreen() = default;

  DebugScreen() {
    lv_group_add_obj(group, screen);

    table = lv_table_create(screen);
    lv_obj_set_size(table, LV_PCT(100), LV_SIZE_CONTENT);

    lv_obj_add_style(table, &g_style->text_tiny, LV_PART_MAIN);
    lv_obj_set_style_border_width(table, 0, LV_PART_MAIN);
    lv_obj_add_style(table, &g_style->table_cell_hr, LV_PART_ITEMS);

#if 0
    lv_obj_add_style(table, &g_style->text_tiny, 0);
    lv_obj_add_style(table, &g_style->container_hr_bottom, 0);
    lv_obj_set_style_pad_top(table, 1, 0);

    lv_obj_add_style(table, 2, &g_style->text_tiny);
    lv_obj_set_style_pad_top(table, 1, 0);

    lv_obj_add_style(table, 3, &g_style->text_medium);
    lv_obj_add_style(table, 3, &g_style->container_hr_bottom);
    lv_obj_set_style_local_pad_top(table, 3, LV_STATE_DEFAULT, 1);
#endif

    lv_table_set_row_cnt(table, 3);
    lv_table_set_col_cnt(table, 5);
    lv_table_set_col_width(table, 0, 30);
    lv_table_set_col_width(table, 1, 25);
    lv_table_set_col_width(table, 2, 28);
    lv_table_set_col_width(table, 3, 9);
    lv_table_set_col_width(table, 4, 33);

    MergeCell(table, 0, 0);
    MergeCell(table, 0, 1);
    MergeCell(table, 0, 2);
    MergeCell(table, 0, 3);

    MergeCell(table, 2, 0);
    MergeCell(table, 2, 1);
    MergeCell(table, 2, 2);
    MergeCell(table, 2, 3);

    // lv_table_set_cell_align(table, 1, 2, LV_LABEL_ALIGN_CENTER);
    lv_table_set_cell_value(table, 1, 3, "G\nI\nC");
    lv_table_set_cell_value(table, 2, 0, " --- no card ---");

#if 0
    lv_table_set_cell_type(table, 2, 0, 2);
    lv_table_set_cell_type(table, 2, 1, 2);
    lv_table_set_cell_type(table, 2, 2, 2);
    lv_table_set_cell_type(table, 2, 3, 2);
    lv_table_set_cell_type(table, 2, 4, 2);
#endif
  }

  void RenderGps(const std::optional<Model::Gps>& gps) {
    if (gps) {
#if 1
      lv_table_set_cell_value_fmt(
          table,
          0,
          0,
          "%c %08.5f %04d-%02d-%02d\n"
          "%c%09.5f %02d:%02d:%02d.%1d",
          // r1c1
          SignChar(gps->latitude),
          std::abs(gps->latitude),
          // r1c2
          gps->year,
          gps->month,
          gps->day,
          // r2c1
          SignChar(gps->longitude),
          std::abs(gps->longitude),
          // r2c2
          gps->hour,
          gps->minute,
          gps->second,
          gps->millisecond / 100);
#endif
    } else {
      lv_table_set_cell_value(
          table,
          0,
          0,
          "? --.----- ****-**-**\n"
          "?---.----- **:**:**.*");
    }
  }

  void RenderImu(const std::optional<Model::Imu>& imu) {
    if (imu) {
      lv_table_set_cell_value_fmt(
          table,
          1,
          0,
          "%+5.2f\n"
          "%+5.2f\n"
          "%+5.2f",
          imu->ax_g,
          imu->ay_g,
          imu->az_g);
      lv_table_set_cell_value_fmt(
          table,
          1,
          1,
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
      lv_table_set_cell_value(
          table,
          1,
          0,
          "?-.--\n"
          "?-.--\n"
          "?-.--");
      lv_table_set_cell_value(
          table,
          1,
          1,
          "?---\n"
          "?---\n"
          "?---");
    }
  }

  void RenderSpeedCourse(const std::optional<Model::Gps>& gps) {
    if (gps) {
      lv_table_set_cell_value_fmt(
          table,
          1,
          2,
          "%03d\n%s",
          (int)std::round(gps->speed_knot * kKnotInMph),
          CourseToString(gps->course_deg));
    } else {
      lv_table_set_cell_value(table, 1, 2, "?\n");
    }
  }

  void RenderThroughput(int dt, const Model::Counter& counter) {
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
    lv_table_set_cell_value_fmt(
        table,
        1,
        4,
        "%d\n"
        "%d\n"
        "%d",
        (int)std::round(average_gps),
        (int)std::round(average_imu),
        (int)std::round(average_can));
  }

  void RenderLoggerPath(const std::optional<Model::Logger>& logger) {
    if (logger) {
#if 1
      lv_table_set_cell_value_fmt(
          table,
          2,
          0,
          ":%02X%02X/%" PRId64 "/%d:%d",
          app::g_device_mac[4],
          app::g_device_mac[5],
          logger->session_id,
          logger->split_id,
          logger->lines);
#else
      lv_table_set_cell_value_fmt(table, 2, 0, ":A7C0/223/10:15631");
#endif
    } else {
      lv_table_set_cell_value(table, 2, 0, " --- no card ---");
    }
  }

  void RenderFast(const Model& model) {
    RenderGps(model.gps);
    RenderImu(model.imu);
    RenderSpeedCourse(model.gps);
  }

  void RenderSlow(int dt, const Model& model) {
    RenderThroughput(dt, model.counter);
    RenderLoggerPath(model.logger);
  }

  void Render(const Model& model) override {
    const TickType_t now = xTaskGetTickCount();
    const int dt = SignedMinus(now, last_time);

    RenderFast(model);
    if (dt >= 1000) {
      RenderSlow(dt, model);
      last_time = now;
    }
  }
};

}  // namespace view
}  // namespace ui
