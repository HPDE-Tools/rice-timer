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
    container = lv_obj_create(parent);
    lv_obj_remove_style_all(container);
    lv_obj_set_size(container, LV_PCT(100), LV_PCT(100));
    lv_obj_center(container);

    debug_view = std::make_unique<DebugView>(container);
  }

  void Render(const Model& model) {
    debug_view->Render(model);
    // TODO
  }
};

}  // namespace view
}  // namespace ui
