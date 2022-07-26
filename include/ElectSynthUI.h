#ifndef _ELECT_SYNTH_UI_H_
#define _ELECT_SYNTH_UI_H_

#include <Arduino.h>
#include <AudioAnalyzeOscilloscope.h>
#include "input_handler.h"
#include "ElectSynth.h"
#include "icons.h"
#include "Display.h"

class ElectSynthUI : public EncoderHandler, public MenuButtonHandler
{
public:
    ElectSynthUI(ElectSynth *synth);

    void draw();
    void update();

    virtual void encoderEvent(int encoder, bool moved_left);
    virtual void encoderButtonEvent(int encoder, bool pressed);
    virtual void menuButtonEvent(BUTTONS button, bool pressed);

protected:
    void drawVCOFormSelection();
    void drawScope();
    void drawVCORatio();
    void drawVCOMix();

    void vcoEncoderEvent(int encoder, bool moved_left);
    void vcoEncoderButtonEvent(int encoder, bool pressed);

    void drawVCFCurve();

    void vcfEncoderEvent(int encoder, bool moved_left);
    void vcfEncoderButtonEvent(int encoder, bool pressed);

    uint8_t page = 1;

    ElectSynth *synth;
    AudioAnalyzeOscilloscope *scope;
    AudioConnection *connection;

    uint8_t vcoAddMod = 1;
    float vcoAddModes[3] = {0.1f, 0.01f, 0.001f};

    uint8_t vcoMixMod = 0;
    float vcoMixModes[3] = {0.1f, 0.01f, 0.001f};


    long vcfFreqMode = 1;
    long vcfQMode = 1;
    float vcfFreqModes[3] = {50.f, 10.0f, 1.0f};
    float vcfQModes[3] = {0.5f, 0.1f, 0.01f};
    int vcfRadius[3] = {5, 3, 1};
};

#endif /* _ELECT_SYNTH_UI_H_ */
