#ifndef _ELECT_SYNTH_H_
#define _ELECT_SYNTH_H_

#include <Audio.h>
#include "audio_constants.h"
#include "Keyboard.h"
#include "ElectVoice.h"

#define ELECT_OSC_MAX_VOICES 4

class ElectSynth : public NoteReceiver
{
public:
    ElectSynth();

    void onNoteOn(int note, int velocity);
    void onNoteOff(int note);

    virtual AudioStream *getOutput();

    void setVCOTable(uint8_t vco, short table);
    void setVCO1Table(short table);
    void setVCO2Table(short table);

    void setVCORatio(float ratio);
    void setVCOMix(float mix);
    void setFilterCutoff(float freq);
    void setFilterResonance(float q);

    void setAttack(float ms);
    void setDecay(float ms);
    void setSustain(float level);
    void setRelease(float ms);

    short getVCOTable(uint8_t vco);
    short getVCO1Table();
    short getVCO2Table();

    float getVCORatio();
    float getVCOMix();

    float getFilterCutoff();
    float getFilterResonance();

    float getAttack();
    float getDecay();
    float getSustain();
    float getRelease();

protected:
    ElectVoice *voices[ELECT_OSC_MAX_VOICES];
    AudioMixer4 *voiceMixer;
    AudioConnection *connections[ELECT_OSC_MAX_VOICES];

    float vcoFreq = 220.0f;
    short vco1Table = WAVEFORM_SINE;
    short vco2Table = WAVEFORM_SAWTOOTH;
    float vcoRatio = 0.5f;
    float vcoMix = 0.5f;

    float filterFreq = 1000.0f;
    float filterQ = 0.0f;

    float attack = 1.5f;
    float decay = 35.0f;
    float sustain = 0.5f;
    float release = 300.0f;

    float voiceStack[ELECT_OSC_MAX_VOICES];
};

#endif /* _ELECT_SYNTH_H_ */
