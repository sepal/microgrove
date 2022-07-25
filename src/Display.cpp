
#include "Display.h"

const int8_t DISPLAY_RESET = -1;

// Screen dimensions
const byte SCREEN_WIDTH = 128;
const byte SCREEN_HEIGHT = 128;

// Extra pins for SPI
const byte DC_PIN = 40;
const byte CS_PIN = 38;
const byte RST_PIN = 41;

Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1, CS_PIN, DC_PIN, RST_PIN);

// Encoder led pins.
const byte enc1LED = 32;
const byte enc2LED = 31;
const byte enc3LED = 30;
const byte enc4LED = 29;

// Color definitions
const uint16_t BLACK = 0x0000;
const uint16_t BLUE = 0x001F;
const uint16_t RED = 0xFA20;
const uint16_t GREEN = 0x47E0;
const uint16_t CYAN = 0x07FF;
const uint16_t MAGENTA = 0xF81F;
const uint16_t PURPLE = 0x6011;
const uint16_t YELLOW = 0xFD60;
const uint16_t WHITE = 0xFFFF;
const uint16_t DARK_GREY = 0x39C7;
const uint16_t LIGHT_GREY = 0x6B6D;
const uint16_t PURE_RED = 0xF800;
const uint16_t MAROON = 0xBAEB;
const uint16_t DARK_GREEN = 0x03A0;


void display_init()
{
    pinMode(enc1LED, OUTPUT);
    pinMode(enc2LED, OUTPUT);
    pinMode(enc3LED, OUTPUT);
    pinMode(enc4LED, OUTPUT);

    display.begin();
    display.fillScreen(BLACK);
    display.fillRect(0, 30, SCREEN_WIDTH, 5, GREEN);

    display.setTextSize(3);
    display.setTextColor(GREEN);
    display.setCursor(0, 40);
    display.println(F("Micro-"));
    display.println(F("groove"));

    display.fillRect(0, 88+5, SCREEN_WIDTH, 5, GREEN);

    delay(1000);
}