// Setup_Chonk.h

#define ST7796_DRIVER     // Confirmed display driver

#define TFT_WIDTH  480
#define TFT_HEIGHT 320

// SPI Pins (Ray Verified™)
#define TFT_MOSI 13
#define TFT_MISO 12
#define TFT_SCLK 14

#define TFT_CS    15
#define TFT_DC     2
#define TFT_RST   -1     // Not connected (wired to EN or 3.3V)
#define TFT_BL    27     // Backlight control pin

// Font options (add/remove as needed)
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define SMOOTH_FONT
