#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>

TFT_eSPI tft = TFT_eSPI();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
  tft.pushColors(reinterpret_cast<uint16_t *>(color_p),
                 (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

void setup() {
  Serial.begin(115200);
  lv_init();
  tft.begin();
  tft.setRotation(1);

  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf1[320 * 10];
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  lv_disp_drv_register(&disp_drv);

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