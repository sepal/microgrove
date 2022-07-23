#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "input.h"

Input input;

void setup()
{
    Serial.begin(9600);
    input.begin();
}

void loop()
{
    input.update();
}