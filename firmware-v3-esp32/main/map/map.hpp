// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Eigen/Core"

#include "common/macros.hpp"
#include "common/polyfill.hpp"
#include "proto/map_generated.h"

namespace map {

/// Lightweight Transverse Mercator projection for local coordinate conversion.
class TransverseMercator {
 public:
  /// Construct with WGS84 ellipsoid parameters and optional scale factor.
  TransverseMercator(double a, double f, double scale = 1.0) : a_(a), f_(f), scale_(scale) {
    // Precompute constants for the projection formulas
    const double e2 = f_ * (2.0 - f_);  // First eccentricity squared
    e_sq_ = e2;
    ep2_ = e2 / (1.0 - e2);           // Second eccentricity squared

    // Authalic radius Q = (1+e^2)/(2*e)*ln((1+e)/(1-e)) - 2/e
    const double e = std::sqrt(e_sq_);
    q_m_ = (1.0 + e_sq_) / (2.0 * e) * std::log((1.0 + e) / (1.0 - e)) - 2.0 / e;

    // Coefficients for series expansion of authalic latitude
    const double ln_qm = std::log(q_m_);
    c0_ = ln_qm * 0.5;                    // C0 = 0.5*ln(Q)
    c1_ = (std::exp(c0_) - std::exp(-c0_)) / 2.0;  // C1 = sinh(C0)

    // Precompute k0 coefficient for scale factor
    const double e4 = e_sq_ * e_sq_;
    const double e6 = e4 * e_sq_;
    const double e8 = e4 * e4;
    k0_ = 1.0 + e_sq_ / 4.0 + 3.0 * e4 / 64.0 + 5.0 * e6 / 256.0 + 175.0 * e8 / 16384.0;
  }

  /// Forward: lat/lon to x,y coordinates using Transverse Mercator projection.
  /// @param lon0 Central meridian (origin longitude) in degrees
  /// @param lat Latitude in degrees
  /// @param lon Longitude in degrees
  /// @param out_x Output x coordinate (scaled by scale_)
  /// @param out_y Output y coordinate
  void Forward(double lon0, double lat, double lon, double& out_x, double& out_y) const {
    // Convert to radians
    const double lam = (lon - lon0) * M_PI / 180.0;   // Central angle in radians
    const double phi = lat * M_PI / 180.0;            // Latitude in radians

    const double sin_phi = std::sin(phi);
    const double cos_phi = std::cos(phi);
    const double tan_phi = std::tan(phi);

    // Radius of curvature in prime vertical: N = a/sqrt(1-e^2*sin^2(phi))
    const double e2s = e_sq_ * sin_phi * sin_phi;
    const double N = a_ / std::sqrt(1.0 - e2s);

    // Transverse Mercator forward formulas (Gauss-Kruger) with higher order terms
    const double v = tan_phi * cos_phi;          // v = tan(phi)*cos(phi)
    const double v2 = v * v;                     // v^2
    const double lam2 = lam * lam;               // lambda^2

    // x coordinate: N*cos(phi)*lambda*(1 + v^2*lambda^2/6*(5-9*e''^2*sin^2(phi)+46*e''^2))
    out_x = scale_ * N * cos_phi * lam *
            (1.0 + v2 * lam2 / 6.0 *
             (5.0 - 9.0 * ep2_ * sin_phi * sin_phi + 46.0 * ep2_));

    // y coordinate with up to lambda^5 term
    const double lam3 = lam2 * lam;              // lambda^3
    out_y = scale_ * N * tan_phi * cos_phi / 2.0 * lam2 *
            (1.0 + lam2 / 24.0 *
             (5.0 + 3.0 * v2 + ep2_ - 9.0 * ep2_ * sin_phi * sin_phi + 46.0 * ep2_));

    // Add higher order term for better accuracy: N*cos(phi)/120*lambda^5*(5-v^2+9*e''^2*sin^2(phi)+4*e''^2)
    const double lam4 = lam3 * lam;              // lambda^4
    out_y += scale_ * N * cos_phi / 120.0 * lam4 *
             (5.0 - v2 + 9.0 * ep2_ * sin_phi * sin_phi + 4.0 * ep2_);
  }

 private:
  double a_;      // Semi-major axis
  double f_;      // Flattening
  double e_sq_;   // First eccentricity squared
  double ep2_;    // Second eccentricity squared
  double scale_;  // Scale factor at central meridian
  double q_m_;    // Authalic radius coefficient Q = (1+e^2)/(2*e)*ln((1+e)/(1-e)) - 2/e
  double c0_;     // C0 = 0.5*ln(Q)
  double c1_;     // C1 = sinh(C0)
  double k0_;     // Scale factor coefficient
};

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
  TransverseMercator ltm_{6378137.0, 1.0 / 298.257223563, /*scale*/ 1.0};
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
