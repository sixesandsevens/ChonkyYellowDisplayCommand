
#include "ui.hpp"
#include "config.hpp"
#include <lvgl.h>
#include <Arduino.h>
#include <time.h>

namespace UI {

  static lv_obj_t* clock_label = nullptr;
  static lv_obj_t* btn1_label = nullptr;
  static lv_style_t UI_STYLE;
  static lv_obj_t* main_screen = nullptr;


  #define UI_COLOR lv_color_hex(0x0000FF) // Blue is Green

  void apply_shared_style(lv_obj_t* obj) {
    static bool initialized = false;
    if (!initialized) {
      lv_style_init(&UI_STYLE);
      lv_style_set_text_color(&UI_STYLE, UI_COLOR);
      lv_style_set_bg_color(&UI_STYLE, lv_color_black());
      initialized = true;
    }
    lv_obj_add_style(obj, &UI_STYLE, LV_PART_MAIN);
  }

  void handle_button_event(lv_event_t* e) {
    Serial.println("🔘 Button pressed");
    lv_label_set_text(btn1_label, "✅ Confirmed");
    lv_obj_set_style_text_color(btn1_label, lv_color_hex(0xFFA500), LV_PART_MAIN);
  }

  void show_main_screen() {
    lv_obj_clean(lv_scr_act());
    init();
  }

  void add_config_button(lv_obj_t* parent) {
    lv_obj_t* config_btn = lv_btn_create(parent);
    lv_obj_align(config_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_add_event_cb(config_btn, [](lv_event_t* e) {
      Serial.println("[UI] Opening Config screen...");
      ConfigUI::show();
    }, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* label = lv_label_create(config_btn);
    lv_label_set_text(label, "Config");
    apply_shared_style(config_btn);
    apply_shared_style(label);
  }

 void init() {
  if (main_screen) {
    lv_obj_del(main_screen);
    main_screen = nullptr;
  }

  main_screen = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(main_screen, lv_color_black(), LV_PART_MAIN);
  lv_scr_load(main_screen);

  // shared style
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_color(&style, UI_COLOR);
  lv_style_set_bg_color(&style, lv_color_black());

  lv_obj_add_style(main_screen, &style, 0);

  // System Ready label
  lv_obj_t *label = lv_label_create(main_screen);
  lv_label_set_text(label, "System Ready");
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
  lv_obj_add_style(label, &style, LV_PART_MAIN);

  // Clock label
  clock_label = lv_label_create(main_screen);
  lv_label_set_text(clock_label, "--:--");
  lv_obj_align(clock_label, LV_ALIGN_TOP_RIGHT, -10, 10);
  lv_obj_add_style(clock_label, &style, LV_PART_MAIN);

  // Main button
  lv_obj_t* btn1 = lv_btn_create(main_screen);
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btn1, handle_button_event, LV_EVENT_CLICKED, NULL);
  lv_obj_add_style(btn1, &style, LV_PART_MAIN);

  btn1_label = lv_label_create(btn1);
  lv_label_set_text(btn1_label, "Activate");
  lv_obj_add_style(btn1_label, &style, LV_PART_MAIN);

  // Config button
  add_config_button(main_screen);
}

  void update_time(const char* time_str) {
    if (clock_label) {
      lv_label_set_text_fmt(clock_label, "%s", time_str);
    }
  }

  void update_status_bar(const char *status_str) {
    Serial.print("Status: ");
    Serial.println(status_str);
  }
}