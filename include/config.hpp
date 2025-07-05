// config.hpp
#pragma once

#include <lvgl.h>

namespace ConfigUI {
  void init();
  void show();
  void hide();
  void apply_theme(lv_color_t color);
}
