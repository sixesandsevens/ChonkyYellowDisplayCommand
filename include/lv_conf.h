#ifndef LV_CONF_H
#define LV_CONF_H

/* Enable 16-bit color */
#define LV_COLOR_DEPTH     16

/* 🔄 Force BGR format (most common on ESP displays like ST7796) */
#define LV_COLOR_16_SWAP   0

/* Optional logging (you already use this) */
#define LV_USE_LOG         1

/* Optional: More memory for widgets */
#define LV_MEM_SIZE        (48U * 1024U)

#endif // LV_CONF_H
