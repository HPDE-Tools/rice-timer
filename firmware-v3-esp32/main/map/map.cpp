// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "map/map.hpp"

#include <algorithm>
#include <numeric>

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
  MakeAdjList();
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

void Map::MakeAdjList() {
  if (!(checkpoints() && checkpoints()->size() > 0 && tracks() && tracks()->size() > 0)) {
    return;
  }
  const int num_v = checkpoints()->size();
  const int num_e = tracks()->size();
  // count degrees
  Eigen::VectorXi out_deg = Eigen::VectorXi::Zero(num_v);
  Eigen::VectorXi in_deg = Eigen::VectorXi::Zero(num_v);
  for (const auto* e : *tracks()) {
    ++out_deg[e->from_checkpoint_index()];
    ++in_deg[e->to_checkpoint_index()];
  }
  // shuffle the edges
  adj_list_buf_.resize(num_e * 2);
  Eigen::VectorXi out_begin = Eigen::VectorXi::Zero(num_v);
  Eigen::VectorXi in_begin = Eigen::VectorXi::Zero(num_v);
  std::partial_sum(out_deg.begin(), out_deg.end() - 1, out_begin.begin() + 1);
  std::partial_sum(in_deg.begin(), in_deg.end() - 1, in_begin.begin() + 1);
  in_begin.array() += num_e;
  Eigen::VectorXi out_i = out_begin;
  Eigen::VectorXi in_i = in_begin;
  for (int ei = 0; ei < num_e; ei++) {
    adj_list_buf_[out_i[track(ei).from_checkpoint_index()]++] = ei;
    adj_list_buf_[in_i[track(ei).to_checkpoint_index()]++] = ei;
  }
  // store in span
  adj_list_.clear();
  adj_list_.reserve(num_v);
  rev_adj_list_.clear();
  rev_adj_list_.reserve(num_v);
  for (int vi = 0; vi < num_v; vi++) {
    adj_list_.emplace_back(&adj_list_buf_[out_begin[vi]], out_deg[vi]);
    rev_adj_list_.emplace_back(&adj_list_buf_[in_begin[vi]], in_deg[vi]);
  }
}

}  // namespace map
