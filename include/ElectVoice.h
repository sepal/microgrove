#ifndef _ELECT_VOICE_H_
#define _ELECT_VOICE_H_

#include <Arduino.h>
#include <Audio.h>

struct ElectVoice
{
    ElectVoice();

    virtual AudioStream *getOutput();

    AudioSynthWaveform *vco1;
    AudioSynthWaveform *vco2;
    AudioMixer4 *vcoMixer;

    AudioSynthWaveformDc *dc;
    AudioEffectEnvelope *filterEnv;
    AudioFilterStateVariable *filter;
    AudioMixer4 *filterMixer;
    AudioEffectEnvelope* env;
    AudioAmplifier* amp;
    AudioConnection *connections[7];
};

#endif /* _ELECT_VOICE_H_ */
