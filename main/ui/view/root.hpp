// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"
#include "ui/view/debug_view.hpp"

namespace ui {
namespace view {

struct Root {
  lv_obj_t* container;

  std::unique_ptr<DebugView> debug_view;

  ~Root() {
    debug_view.reset();

    lv_obj_del(container);
  }

  Root(lv_obj_t* parent) {
    container = lv_cont_create(parent, nullptr);
    lv_obj_align(container, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_obj_set_auto_realign(container, true);
    lv_obj_reset_style_list(container, 0);
    lv_cont_set_fit2(container, LV_FIT_MAX, LV_FIT_MAX);
    lv_cont_set_layout(container, LV_LAYOUT_PRETTY_MID);

    debug_view = std::make_unique<DebugView>(container);
  }

  void Render(const Model& model) {
    debug_view->Render(model);
    // TODO
  }
};

}  // namespace view
}  // namespace ui
