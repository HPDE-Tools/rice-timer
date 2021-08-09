// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "map/map_index.hpp"

#include "flatbuffers/util.h"

#include "common/macros.hpp"
#include "io/fs_utils.hpp"

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
    ESP_LOG_BUFFER_HEXDUMP(TAG, file_content.data(), file_content.size(), ESP_LOG_INFO);

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

}  // namespace map
