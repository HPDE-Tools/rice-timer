// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

namespace ui {
namespace view {

struct TrackTimerScreen : public Screen {
  virtual ~TrackTimerScreen() = default;
  TrackTimerScreen() {
    // TODO
    {
      lv_obj_t* const label = lv_label_create(screen);
      lv_obj_add_style(label, &g_style->text_serif, 0);
      lv_obj_center(label);
      lv_label_set_text_static(label, "TODO Track Timer");
    }
  }

  virtual void Render(const Model& model) {
    // TODO
  }
};

}  // namespace view
}  // namespace ui
