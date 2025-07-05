#include "main.hpp"
#include "ui.hpp"
#include <ESP323248S035.hpp>
#include <time.h>  // ⏰ Real time support
#include <esp_heap_caps.h>
#include <esp_system.h>
#include "lvgl.h"


#define LV_HOR_RES_MAX     320
#define SCREEN_BUF_SIZE    (LV_HOR_RES_MAX * 20)

static lv_color_t *buf1;

void setup() {
    Serial.begin(115200);

    buf1 = (lv_color_t *)heap_caps_malloc(SCREEN_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    if (!buf1) {
        Serial.println("Failed to allocate display buffer in PSRAM!");
    } else {
        Serial.printf("Display buffer allocated at %p, size: %u bytes\n", buf1, SCREEN_BUF_SIZE * sizeof(lv_color_t));
    }

    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    target.init();                 // Init LVGL, display, and input
    // Ensure the LCD backlight is fully enabled
    bsp::ESP323248S035C<Main>::set_backlight(255);
    lv_obj_clean(lv_scr_act());   // Clear splash screen
    UI::init();                   // Create main interface (now includes config button)

    if (!psramFound()) {
        Serial.println("PSRAM not found!");
    } else {
        Serial.println("PSRAM found and enabled.");
    }


    Serial.printf("Free heap: %u bytes\n", ESP.getFreeHeap());
    Serial.printf("Free PSRAM: %u bytes\n", ESP.getFreePsram());
}

void loop() {
    static unsigned long last_update = 0;
    unsigned long now = millis();

    target.update();  // Keep LVGL alive

    // Update clock every 5 seconds
    if (now - last_update > 5000) {
        last_update = now;

        time_t raw_time = time(nullptr);
        struct tm *t = localtime(&raw_time);

        if (t) {
            char time_str[6];
            snprintf(time_str, sizeof(time_str), "%02d:%02d", t->tm_hour, t->tm_min);
            UI::update_time(time_str);
        } else {
            UI::update_time("??:??");
        }
    }
}

template<>
const bsp::TPC_LCD<
  bsp::Atomic<std::mutex, std::unique_lock<std::mutex>>,
  bsp::SPIImpl<SPIClass>,
  bsp::I2CImpl<TwoWire>
>::log_type bsp::TPC_LCD<
  bsp::Atomic<std::mutex, std::unique_lock<std::mutex>>,
  bsp::SPIImpl<SPIClass>,
  bsp::I2CImpl<TwoWire>
>::log = [](lv_log_level_t ll, const char *msg) {
  static const char *pre[LV_LOG_LEVEL_NUM] = {
    "[-] ", // TRACE
    "[=] ", // INFO
    "[~] ", // WARN
    "[!] ", // ERROR
    "[+] "  // USER
  };
  unsigned level = static_cast<unsigned>(ll);
  if (level < LV_LOG_LEVEL_NONE) {
    Serial.print(pre[level]);
  }
  Serial.println(msg);
};


#if (LV_USE_LOG)
// Optional logging hook
extern "C" void my_lv_log_cb(lv_log_level_t ll, const char *msg) {
  static const char *pre[LV_LOG_LEVEL_NUM] = {
    "[-] ", // TRACE
    "[=] ", // INFO
    "[~] ", // WARN
    "[!] ", // ERROR
    "[+] "  // USER
  };
  unsigned level = static_cast<unsigned>(ll);
  if (level < LV_LOG_LEVEL_NONE) {
    Serial.print(pre[level]);
  }
  Serial.println(msg);
}
#endif
