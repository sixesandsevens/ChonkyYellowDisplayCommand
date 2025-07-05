#include "main.hpp"
#include "ui.hpp"
#include <ESP323248S035.hpp>
#include <time.h>  // ⏰ Real time support

void setup() {
  Serial.begin(115200);

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  target.init();                 // Init LVGL, display, and input
  lv_obj_clean(lv_scr_act());   // Clear splash screen
  UI::init();                   // Create main interface (now includes config button)
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
