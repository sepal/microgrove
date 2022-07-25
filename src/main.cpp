#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "input.h"
#include "Keyboard.h"
#include "ElectSynth.h"

Input input;
Keyboard keyboard;
ElectSynth* synth;
AudioConnection* connections[3];
AudioOutputI2S* i2s1;
AudioControlSGTL5000* codec;



void setup()
{
    Serial.begin(9600);

    Serial.println("init connections");
    synth = new ElectSynth();
    i2s1 = new AudioOutputI2S();
    connections[0] = new AudioConnection(*synth->getOutput(), 0, *i2s1, 0);
    connections[1] = new AudioConnection(*synth->getOutput(), 0, *i2s1, 1);

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
    Serial.println("ready");

    AudioMemory(24);
    AudioInterrupts();
}

void loop()
{
    input.update();
}