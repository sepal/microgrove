#ifndef _ELECT_SYNTH_H_
#define _ELECT_SYNTH_H_

#include <Audio.h>
#include "audio_constants.h"
#include "Keyboard.h"
#include "ElectVoice.h"

#define ELECT_OSC_MAX_VOICES 1

class ElectSynth: public NoteReceiver
{
public:
    ElectSynth();

    void onNoteOn(int note, int velocity);
    void onNoteOff(int note);

    virtual AudioStream *getOutput();

    void setVCO1Table(short table);
    void setVCO2Table(short table);

    void setVCODetune(float ratio);
    void setVCOMix(float mix);
    void setFilterCutoff(float freq);
    void setFilterResonance(float q);

    void setAttack(float ms);
    void setDecay(float ms);
    void setSustain(float level);
    void setRelease(float ms);


protected:
    ElectVoice *voices[ELECT_OSC_MAX_VOICES];
    AudioMixer4 *voiceMixer;
    AudioConnection *connections[ELECT_OSC_MAX_VOICES];


    short vco1Table = WAVEFORM_SINE;
    short vco2Table = WAVEFORM_SAWTOOTH;
    float vcoRatio = 0.5f;
    float vcoMix = 0.5f;

    float freq = 1.0f;
    float q = 0.0f;

    float attack = 1.5f;
    float decay = 35.0f;
    float sustain = 0.5f;
    float release = 300.0f;
};


#endif /* _ELECT_SYNTH_H_ */
