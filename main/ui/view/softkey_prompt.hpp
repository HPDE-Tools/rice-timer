// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

namespace ui {
namespace view {

struct SoftkeyPrompt {
  lv_obj_t* box;

  ~SoftkeyPrompt() { lv_obj_del(box); }

  SoftkeyPrompt(/*align*/) {
    box = lv_obj_create(lv_layer_top());
    lv_obj_add_flag(box, LV_OBJ_FLAG_HIDDEN);
  }
};

}  // namespace view
}  // namespace ui
