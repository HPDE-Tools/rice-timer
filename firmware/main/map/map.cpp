// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "map/map.hpp"

#include "common/macros.hpp"
#include "io/fs_utils.hpp"
#include "proto/map_generated.h"

namespace map {

namespace {

constexpr char TAG[] = "map";

}  // namespace

Map::Map() {}

Map::Map(std::string&& proto_data) : proto_data_(proto_data) {
  proto_ = ricetimer::proto::GetMap(proto_data_.data());
  InitializeProjection();
}

void Map::InitializeProjection() {
  const ricetimer::proto::LatLonD* proto_origin =
      CHECK_NOTNULL(CHECK_NOTNULL(proto_->header())->origin());
  origin_lat_ = proto_origin->lat();
  origin_lon_ = proto_origin->lon();
  double unused_origin_x_;
  ltm_.Forward(origin_lon_, origin_lat_, origin_lon_, /*out*/ unused_origin_x_, /*out*/ origin_y_);
}

std::unique_ptr<Map> Map::FromFile(const std::string& path) {
  std::string file_content{};
  OK_OR_RETURN(io::ReadBinaryFileToString(path, &file_content), nullptr);
  ESP_LOG_BUFFER_HEXDUMP(TAG, file_content.data(), file_content.size(), ESP_LOG_VERBOSE);
  std::unique_ptr<Map> map{new Map(std::move(file_content))};
  return map;
}

Eigen::Vector2f Map::LatLonToLtm(double lat, double lon) const {
  double x = NAN;
  double y = NAN;
  ltm_.Forward(origin_lon_, lat, lon, /*out*/ x, /*out*/ y);
  y -= origin_y_;
  return {x, y};
}

}  // namespace map
