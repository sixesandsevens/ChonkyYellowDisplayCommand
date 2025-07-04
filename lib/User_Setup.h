#define ST7796_DRIVER

#define TFT_WIDTH  480
#define TFT_HEIGHT 320

#define TFT_CS   15
#define TFT_DC   33
#define TFT_RST  -1  // Tied to EN or not used

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_MISO 19  // Used for SD card

#define TOUCH_CS 21
#define TOUCH_IRQ 36

#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY 2500000

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT
