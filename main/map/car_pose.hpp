// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

namespace map {

struct CarPose {
  float rel_easting;
  float rel_northing;
  float height;
  float speed_over_ground;
  float course_over_ground_deg;

  // TODO(summivox): rotational data
};

}  // namespace map
