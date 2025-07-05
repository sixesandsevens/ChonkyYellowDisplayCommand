
#pragma once
#include <lvgl.h>

namespace UI {
  void init();
  void update_time(const char* time_str);
  void update_status_bar(const char* status_str);
  void show_main_screen();
  void add_config_button(lv_obj_t* parent);
  void apply_shared_style(lv_obj_t* obj);  // New function
}