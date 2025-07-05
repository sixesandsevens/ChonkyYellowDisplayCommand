#include "config.hpp"
#include <lvgl.h>
#include <Arduino.h>
#include <WiFi.h>

namespace ConfigUI {
  static lv_obj_t* config_screen;
  static lv_obj_t* wifi_screen;
  static lv_obj_t* ssid_input;
  static lv_obj_t* pass_input;

  void handle_back_button(lv_event_t* e);

  void handle_wifi_connect(lv_event_t* e) {
    const char* ssid = lv_textarea_get_text(ssid_input);
    const char* pass = lv_textarea_get_text(pass_input);

    Serial.printf("[Wi-Fi] Connecting to SSID: %s\n", ssid);
    WiFi.begin(ssid, pass);
  }

  void show_wifi_input_screen() {
    wifi_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(wifi_screen, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* label1 = lv_label_create(wifi_screen);
    lv_label_set_text(label1, "SSID:");
    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 10, 10);

    ssid_input = lv_textarea_create(wifi_screen);
    lv_obj_align(ssid_input, LV_ALIGN_TOP_LEFT, 10, 30);
    lv_obj_set_width(ssid_input, 200);

    lv_obj_t* label2 = lv_label_create(wifi_screen);
    lv_label_set_text(label2, "Password:");
    lv_obj_align(label2, LV_ALIGN_TOP_LEFT, 10, 70);

    pass_input = lv_textarea_create(wifi_screen);
    lv_obj_align(pass_input, LV_ALIGN_TOP_LEFT, 10, 90);
    lv_textarea_set_password_mode(pass_input, true);
    lv_obj_set_width(pass_input, 200);

    lv_obj_t* connect_btn = lv_btn_create(wifi_screen);
    lv_obj_align(connect_btn, LV_ALIGN_TOP_LEFT, 10, 130);
    lv_obj_add_event_cb(connect_btn, handle_wifi_connect, LV_EVENT_CLICKED, nullptr);
    lv_obj_t* label = lv_label_create(connect_btn);
    lv_label_set_text(label, "Connect");

    lv_obj_t* back_btn = lv_btn_create(wifi_screen);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(back_btn, handle_back_button, LV_EVENT_CLICKED, nullptr);
    lv_obj_t* back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "← Back");

    lv_scr_load(wifi_screen);
  }

  void handle_wifi_button(lv_event_t* e) {
    Serial.println("[Wi-Fi] Configure Wi-Fi pressed");
    show_wifi_input_screen();
  }

  void handle_theme_toggle(lv_event_t* e) {
    Serial.println("[Theme] Toggle theme pressed");
    // TODO: swap global UI_COLOR and re-apply styles
  }

  void handle_time_sync(lv_event_t* e) {
    Serial.println("[Time] Sync time pressed");
    // TODO: trigger NTP or RTC fetch
  }

  void handle_back_button(lv_event_t* e) {
    Serial.println("[Config] Back to main screen");
    extern void return_to_main_screen();
    return_to_main_screen();
  }

  void create_config_button(const char* label_text, lv_align_t align, lv_coord_t y_ofs, lv_event_cb_t cb) {
    lv_obj_t* btn = lv_btn_create(config_screen);
    lv_obj_align(btn, align, 0, y_ofs);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, label_text);
  }

  void init() {
    config_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(config_screen, lv_color_black(), LV_PART_MAIN);

    create_config_button("Connect to Wi-Fi", LV_ALIGN_TOP_MID, 20, handle_wifi_button);
    create_config_button("Toggle Theme", LV_ALIGN_TOP_MID, 70, handle_theme_toggle);
    create_config_button("Sync Time", LV_ALIGN_TOP_MID, 120, handle_time_sync);
    create_config_button("← Back", LV_ALIGN_BOTTOM_MID, -20, handle_back_button);
  }

  void show() {
    if (!config_screen) init();
    lv_scr_load(config_screen);
  }
}
