// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Eigen/Core"
#include "GeographicLib/TransverseMercator.hpp"

#include "common/macros.hpp"
#include "common/polyfill.hpp"
#include "proto/map_generated.h"

namespace map {

class Map {
 public:
  static std::unique_ptr<Map> FromFile(const std::string& path);

  Eigen::Vector2f LatLonToLtm(double lat, double lon) const;
  Eigen::Vector2f LatLonToLtm(Eigen::Vector2d latlon) const {
    return LatLonToLtm(latlon[0], latlon[1]);
  }
  Eigen::Vector2f LlhToLtm(Eigen::Vector3d llh) const { return LatLonToLtm(llh[0], llh[1]); }

  auto checkpoints() const { return proto_->checkpoints(); }
  auto& checkpoint(int i) const { return *(*CHECK_NOTNULL(checkpoints()))[i]; }
  auto tracks() const { return proto_->tracks(); }
  auto& track(int i) const { return *(*CHECK_NOTNULL(tracks()))[i]; }

  const std::vector<std::span<const int>>& adj_list() const { return adj_list_; }
  const std::vector<std::span<const int>>& rev_adj_list() const { return rev_adj_list_; }

 protected:
  Map();
  explicit Map(std::string&& proto_data);

 private:
  std::string proto_data_{};
  const ricetimer::proto::Map* proto_ = nullptr;  // aliased from proto_data_

  /// local transverse mercator projection, unscaled WGS-84
  GeographicLib::TransverseMercator ltm_{
      GeographicLib::Constants::WGS84_a(),
      GeographicLib::Constants::WGS84_f(),
      /*scale*/ 1.0,
  };
  double origin_lat_;
  double origin_lon_;
  double origin_y_;

  std::vector<int> adj_list_buf_;
  std::vector<std::span<const int>> adj_list_;
  std::vector<std::span<const int>> rev_adj_list_;

  void InitializeProjection();
  void MakeAdjList();
};

}  // namespace map
