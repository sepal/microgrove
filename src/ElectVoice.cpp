#include "ElectVoice.h"

ElectVoice::ElectVoice()
{
    this->vco1 = new AudioSynthWaveform();
    this->vco2 = new AudioSynthWaveform();
    this->vco1->amplitude(1.0);
    this->vco2->amplitude(1.0);
    this->vco1->begin(WAVEFORM_SINE);
    this->vco2->begin(WAVEFORM_SAWTOOTH);

    this->vcoMixer = new AudioMixer4();

    this->connections[0] = new AudioConnection(*this->vco1, 0, *this->vcoMixer, 0);
    this->connections[1] = new AudioConnection(*this->vco2, 0, *this->vcoMixer, 1);
    this->vcoMixer->gain(0, 0.5);
    this->vcoMixer->gain(1, 0.5);

    this->dc = new AudioSynthWaveformDc();
    this->filterEnv = new AudioEffectEnvelope();
    this->connections[2] = new AudioConnection(*this->dc, *this->filterEnv);
    this->filter = new AudioFilterStateVariable();
    this->connections[3] = new AudioConnection(*this->vcoMixer, 0, *this->filter, 0);
    this->connections[4] = new AudioConnection(*this->filterEnv, 0, *this->filter, 1);

    this->dc->amplitude(20.0);
    this->filterEnv->attack(0.5f);
    this->filterEnv->decay(100);
    this->filterEnv->sustain(0);
    this->filterEnv->release(100);
    this->filter->octaveControl(2.0f);

    this->env = new AudioEffectEnvelope();
    this->connections[5] = new AudioConnection(*this->filter, *this->env);

    this->amp = new AudioAmplifier();
    this->connections[6] = new AudioConnection(*this->env, *this->amp);
}

AudioStream *ElectVoice::getOutput()
{
    return this->env;
}