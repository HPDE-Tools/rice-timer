// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "map/map_index.hpp"

#include "flatbuffers/util.h"

#include "common/macros.hpp"
#include "io/fs_utils.hpp"
#include "map/utils.hpp"

namespace map {

namespace {
constexpr char TAG[] = "map_index";
}  // namespace

MapIndex::MapIndex() : mutex_(xSemaphoreCreateMutex()){};

RustMutexGuard<MapIndex> MapIndex::GetInstance() {
  static RustMutex<MapIndex> instance{};
  return instance.Lock();
}

esp_err_t MapIndex::Load(std::string_view map_data_path) {
  map_data_path_ = map_data_path;
  std::string file_content;  // reuse internal buffer
  for (dirent* file_info : io::DirIter(map_data_path_.c_str())) {
    if (file_info->d_type != DT_REG) {
      continue;
    }
    std::string file_path = map_data_path_ + '/' + file_info->d_name;
    ESP_LOGI(TAG, "read file: %s", file_path.c_str());
    TRY(io::ReadBinaryFileToString(file_path, &file_content));
    ESP_LOG_BUFFER_HEXDUMP(TAG, file_content.data(), file_content.size(), ESP_LOG_VERBOSE);

    const ricetimer::proto::Map* map = ricetimer::proto::GetMap(file_content.data());
    Entry& entry = entries_.emplace_back();
    entry.path = std::move(file_path);
    entry.name = map->header()->name()->str();
    entry.origin_latlon << map->header()->origin()->lat(), map->header()->origin()->lon();
    entry.type = map->header()->type();

    ESP_LOGI(
        TAG,
        "map read: %s (%+10.5f, %+10.5f)",
        entry.name.c_str(),
        entry.origin_latlon[0],
        entry.origin_latlon[1]);
  }
  return ESP_OK;
}

std::pair<const MapIndex::Entry*, double> MapIndex::GetNearestMap(const Eigen::Vector2d& latlon) {
  CHECK(!entries_.empty());
  // TODO: use some kind of nearest neighbor impl
  // ESP_LOGE(TAG, "GetNearestMap(%+9.5f, %+10.5f)", latlon[0], latlon[1]);  // DEBUG
  double min_distance = 1e100;
  const Entry* min_entry = nullptr;
  for (const Entry& entry : entries_) {
    const double distance = GeodesicDistance(entry.origin_latlon, latlon);
    // ESP_LOGW(TAG, "- %s: %.3f", entry.name.c_str(), distance);  // DEBUG
    if (distance < min_distance) {
      min_distance = distance;
      min_entry = &entry;
    }
  }
  return {min_entry, min_distance};
}

}  // namespace map
