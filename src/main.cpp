#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "Display.h"
#include "input.h"
#include "Keyboard.h"
#include "ElectSynth.h"
#include "ElectSynthUI.h"

#define PIN_VOLUME 15

Input input;
Keyboard keyboard;
ElectSynth *synth;
ElectSynthUI *electUI;
AudioConnection *connections[5];
AudioOutputI2S *i2s1;
AudioOutputUSB *usb;
AudioControlSGTL5000 *codec;

int vol = 50;

void setup()
{
    usb = new AudioOutputUSB();
    usb->begin();
    Serial.begin(9600);

    display_init();

    Serial.println("init connections");
    synth = new ElectSynth();
    electUI = new ElectSynthUI(synth);
    i2s1 = new AudioOutputI2S();
    connections[0] = new AudioConnection(*synth->getOutput(), 0, *i2s1, 0);
    connections[1] = new AudioConnection(*synth->getOutput(), 0, *i2s1, 1);
    connections[2] = new AudioConnection(*synth->getOutput(), 0, *usb, 0);
    connections[3] = new AudioConnection(*synth->getOutput(), 0, *usb, 1);



    codec = new AudioControlSGTL5000();
    codec->enable();
    codec->volume(0.2); // caution: very loud - use oscilloscope only!
    codec->dacVolumeRamp();
    codec->lineOutLevel(13);
    codec->volume(0.45);


    Serial.println("init input");
    input.begin();
    input.setKeyboardHandler(&keyboard);
    keyboard.setReceiver(synth);
    input.setEncoderHandler(electUI);
    input.setMenuButtonHandler(electUI);
    input.setUtilityButtonHandler(&keyboard);
    Serial.println("ready");

    AudioMemory(24);
    AudioInterrupts();
    display.fillScreen(BLACK);
    electUI->draw();
}

void loop()
{
    int n = analogRead(PIN_VOLUME);

    if (n != vol) {
        vol = n;
        codec->volume((float) n / 1023);
    }

    input.update();
    electUI->update();
}