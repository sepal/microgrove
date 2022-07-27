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
    void drawVCFDecay();
    void drawVCFEnv();

    void vcfEncoderEvent(int encoder, bool moved_left);
    void vcfEncoderButtonEvent(int encoder, bool pressed);

    void drawADSR();

    void adsrEncoderEvent(int encoder, bool moved_left);
    void adsrEncoderButtonEvent(int encoder, bool pressed);

    uint8_t page = 1;

    ElectSynth *synth;
    AudioAnalyzeOscilloscope *scope;
    AudioConnection *connection;

    uint8_t vcoAddMod = 1;
    float vcoAddModes[3] = {0.1f, 0.01f, 0.001f};

    uint8_t vcoMixMod = 0;
    float vcoMixModes[3] = {0.1f, 0.01f, 0.001f};

    uint8_t vcfMode[4] = {0, 0, 0, 0};

    uint8_t vcfPrecessionPos[2][3] = {
        {12, 18, 30},
        {0, 12, 18}
    };
    
    float vcfModes[4][3] = {
        {50.f, 10.0f, 1.0f},
        {0.5f, 0.1f, 0.01f},
        {50.0f, 1.0f, 0.1f},
        {1.f, 0.1f, 0.01f},
    };

    int modeRadius[3] = {5, 3, 1};

    uint8_t adsrMode[4] = {0, 0, 0, 0};
    float adsrModes[4][3] = {
        {50.0f, 1.0f, 0.1f},
        {50.0f, 1.0f, 0.1f},
        {0.1f, 0.05f, 0.01f},
        {50.0f, 1.0f, 0.1f},
    };
};

#endif /* _ELECT_SYNTH_UI_H_ */
