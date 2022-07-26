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

    short getPrevWaveform(short table);
    short getNextWaveform(short table);

    virtual void encoderEvent(int encoder, bool moved_left);
    virtual void encoderButtonEvent(int encoder, bool pressed);

protected:
    void drawVCOFormSelection(int16_t x, int16_t y, uint16_t active_color, short form);
    void drawScope();
    void drawVCORatio();
    void drawVCOMix();


    ElectSynth *synth;
    AudioAnalyzeOscilloscope *scope;
    AudioConnection *connection;
};

#endif /* _ELECT_SYNTH_UI_H_ */
