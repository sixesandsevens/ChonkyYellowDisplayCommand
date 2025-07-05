#ifndef LV_CONF_H
#define LV_CONF_H

#include "lvgl.h"
#include "esp_heap_caps.h"
#include <Arduino.h>

/* Enable 16-bit color */
#define LV_COLOR_DEPTH     16

/* 🔄 Force BGR format (most common on ESP displays like ST7796) */
#define LV_COLOR_16_SWAP   0

/* Optional logging (you already use this) */
#define LV_USE_LOG         1

/* Optional: More memory for widgets */
#define LV_MEM_SIZE        (16U * 1024U)
#define LV_MEM_CUSTOM 1
#define LV_MEM_CUSTOM_ALLOC  my_malloc
#define LV_MEM_CUSTOM_FREE   my_free

static inline void *my_malloc(size_t size) {
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
}
static inline void my_free(void *ptr) {
    heap_caps_free(ptr);
}

/* Define the horizontal resolution of your display (adjust as needed) */
#define LV_HOR_RES_MAX     320

/* Define the screen buffer size (adjust as needed) */
#define SCREEN_BUF_SIZE    (LV_HOR_RES_MAX * 10)

/* Disable all built-in fonts except the smallest you need */
#define LV_FONT_MONTSERRAT_8     0
#define LV_FONT_MONTSERRAT_10    0
#define LV_FONT_MONTSERRAT_12    0
#define LV_FONT_MONTSERRAT_14    0
#define LV_FONT_MONTSERRAT_16    0
#define LV_FONT_MONTSERRAT_18    0
#define LV_FONT_MONTSERRAT_20    0
#define LV_FONT_MONTSERRAT_22    0
#define LV_FONT_MONTSERRAT_24    0
#define LV_FONT_MONTSERRAT_26    0
#define LV_FONT_MONTSERRAT_28    0
#define LV_FONT_MONTSERRAT_30    0
#define LV_FONT_MONTSERRAT_32    0
#define LV_FONT_MONTSERRAT_34    0
#define LV_FONT_MONTSERRAT_36    0
#define LV_FONT_MONTSERRAT_38    0
#define LV_FONT_MONTSERRAT_40    0
#define LV_FONT_MONTSERRAT_42    0
#define LV_FONT_MONTSERRAT_44    0
#define LV_FONT_MONTSERRAT_46    0
#define LV_FONT_MONTSERRAT_48    0
#define LV_FONT_UNSCII_8         0
#define LV_FONT_UNSCII_16        0
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0
#define LV_FONT_SIMSUN_16_CJK    0
#define LV_FONT_SIMSUN_14_CJK    0
#define LV_FONT_SOURCE_HAN_SANS_SC_16_CJK 0
#define LV_FONT_SOURCE_HAN_SANS_SC_14_CJK 0

// Enable only the font(s) you actually use, e.g.:
#define LV_FONT_MONTSERRAT_14    1

#endif // LV_CONF_H
