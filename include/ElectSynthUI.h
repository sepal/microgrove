#ifndef _ELECT_SYNTH_UI_H_
#define _ELECT_SYNTH_UI_H_

#include <Arduino.h>
#include "input_handler.h"
#include "ElectSynth.h"

class ElectSynthUI : public EncoderHandler
{
public:
    ElectSynthUI(ElectSynth *synth);

    virtual void encoderEvent(int encoder, bool moved_left);
    virtual void encoderButtonEvent(int encoder, bool pressed);

protected:
    ElectSynth *synth;
};

#endif /* _ELECT_SYNTH_UI_H_ */
