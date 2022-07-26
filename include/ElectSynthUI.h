#ifndef _ELECT_SYNTH_UI_H_
#define _ELECT_SYNTH_UI_H_

#include <Arduino.h>
#include <AudioAnalyzeOscilloscope.h>
#include "input_handler.h"
#include "ElectSynth.h"
#include "icons.h"
#include "Display.h"

class ElectSynthUI : public EncoderHandler
{
public:
    ElectSynthUI(ElectSynth *synth);

    void draw();
    void update();

    virtual void encoderEvent(int encoder, bool moved_left);
    virtual void encoderButtonEvent(int encoder, bool pressed);

protected:
    void drawVCOFormSelection();
    void drawScope();
    void drawVCORatio();
    void drawVCOMix();

    ElectSynth *synth;
    AudioAnalyzeOscilloscope *scope;
    AudioConnection *connection;

    uint8_t vcoAddMod = 1;
    float vcoAddModes[3] = {0.1f, 0.01f, 0.001f};

    uint8_t vcoMixMod = 0;
    float vcoMixModes[3] = {0.1f, 0.01f, 0.001f};


    uint8_t vcfMode = 0;
};

#endif /* _ELECT_SYNTH_UI_H_ */
