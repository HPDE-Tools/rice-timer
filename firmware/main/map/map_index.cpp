// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "map/map_index.hpp"

#include "flatbuffers/util.h"

#include "common/macros.hpp"
#include "io/fs_utils.hpp"
#include "map/utils.hpp"

namespace map {

using ricetimer::proto::Map;
using ricetimer::proto::MapHeader;

namespace {
constexpr char TAG[] = "map_index";
}

MapIndex::MapIndex() = default;

MapIndex* MapIndex::GetInstance() {
  static MapIndex instance{};
  return &instance;
}

esp_err_t MapIndex::Load(std::string_view map_data_path) {
  map_data_path_ = map_data_path;
  std::string file_content;  // reuse internal buffer
  for (auto ff_info : io::DirIter(map_data_path_.c_str())) {
    std::string path = SD_VFS_ROOT + map_data_path_.substr(2) + "/" + ff_info->fname;  // HACK
    ESP_LOGI(TAG, "read file: %s", path.c_str());
    TRY(io::ReadBinaryFileToString(path, &file_content));
    ESP_LOG_BUFFER_HEXDUMP(TAG, file_content.data(), file_content.size(), ESP_LOG_VERBOSE);

    const Map* map = ricetimer::proto::GetMap(file_content.data());
    Entry& entry = entries_.emplace_back();
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

const MapIndex::Entry& MapIndex::GetNearestMap(const Eigen::Vector2d& latlon) {
  CHECK(!entries_.empty());
  // TODO: use some kind of nearest neighbor impl
  ESP_LOGE(TAG, "GetNearestMap(%+9.5f, %+10.5f)", latlon[0], latlon[1]);  // DEBUG
  double min_distance = 1e100;
  const Entry* min_entry = nullptr;
  for (const Entry& entry : entries_) {
    const double distance = GeodesicDistance(entry.origin_latlon, latlon);
    ESP_LOGW(TAG, "- %s: %.3f", entry.name.c_str(), distance);  // DEBUG
    if (distance < min_distance) {
      min_distance = distance;
      min_entry = &entry;
    }
  }
  return *min_entry;
}

}  // namespace map
