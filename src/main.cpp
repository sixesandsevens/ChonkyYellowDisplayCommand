#include <lvgl.h>
#include <src/drivers/display/tft_espi/lv_tft_espi.h>
#include <Arduino.h>

static lv_display_t *disp;

void setup() {
  Serial.begin(115200);
  lv_init();

  static lv_color_t buf1[480 * 10];
  disp = lv_tft_espi_create(480, 320, buf1, sizeof(buf1));
  if(disp) {
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);
  }

  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Hello, Chonky Display!");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void loop() {
  static uint32_t last = millis();
  uint32_t now = millis();
  lv_tick_inc(now - last);
  last = now;
  lv_timer_handler();
  delay(5);
}