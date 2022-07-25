#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>


// OLed Display.
extern Adafruit_SSD1351 display;

// Encoder led pins.
extern const byte enc1LED;
extern const byte enc2LED;
extern const byte enc3LED;
extern const byte enc4LED;

// Color definitions
extern const uint16_t BLACK;
extern const uint16_t BLUE;
extern const uint16_t RED;
extern const uint16_t GREEN;
extern const uint16_t CYAN;
extern const uint16_t MAGENTA;
extern const uint16_t PURPLE;
extern const uint16_t YELLOW;
extern const uint16_t WHITE;
extern const uint16_t DARK_GREY;
extern const uint16_t LIGHT_GREY;
extern const uint16_t PURE_RED;
extern const uint16_t MAROON;
extern const uint16_t DARK_GREEN;

void display_init();

#endif /* _DISPLAY_H_ */
