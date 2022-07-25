#include "ElectSynth.h"

ElectSynth::ElectSynth()
{
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i] = new ElectVoice();
    }

    this->voiceMixer = new AudioMixer4();
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voiceMixer->gain(i, 0.25);
        this->connections[i] = new AudioConnection(*this->voices[i]->getOutput(), 0, *this->voiceMixer, i);
    }
}

void ElectSynth::onNoteOn(int note, int velocity)
{
    float vcoFreq = NOTE_FREQ[note];

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        if (this->voiceStack[i] == 0) {
            this->voices[i]->vco1->frequency(vcoFreq);
            this->voices[i]->vco2->frequency(vcoFreq * this->vcoRatio);
            this->voices[i]->env->noteOn();
            this->voiceStack[i] = vcoFreq;
            return;
        }
    }
    
}

void ElectSynth::onNoteOff(int note)
{

    float vcoFreq = NOTE_FREQ[note];
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        if (this->voiceStack[i] == vcoFreq) {
            this->voices[i]->env->noteOff();
            this->voiceStack[i] = 0;
        }
    }
}

AudioStream *ElectSynth::getOutput()
{
    return this->voiceMixer;
}

void ElectSynth::setVCO1Table(short table)
{
    this->vco1Table = table;
    AudioNoInterrupts();
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vco1->begin(vco1Table);
    }
    AudioInterrupts();
}

void ElectSynth::setVCO2Table(short table)
{
    this->vco2Table = table;
    AudioNoInterrupts();
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vco2->begin(this->vco2Table);
    }
    AudioInterrupts();
}

void ElectSynth::setVCORatio(float ratio)
{
    this->vcoRatio = ratio;

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        if (this->voiceStack[i] > 0) {
            this->voices[i]->vco2->frequency(this->voiceStack[i] * this->vcoRatio);
        }
    }
}

void ElectSynth::setVCOMix(float mix)
{
    if (mix >= 0.0 && mix <=1.0) {
        this->vcoMix = mix;
    }

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vcoMixer->gain(0, 1.0 * vcoMix);
        this->voices[i]->vcoMixer->gain(1, 1.0 * (1.0f - vcoMix));
    }
}

void ElectSynth::setFilterCutoff(float freq)
{
    this->filterFreq = freq;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->frequency(filterFreq);
    }
}

void ElectSynth::setFilterResonance(float q)
{
    this->filterQ = q;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->resonance(filterQ);
    }
}

void ElectSynth::setAttack(float ms)
{
    this->attack = ms;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->attack(ms);
    }
}

void ElectSynth::setDecay(float ms)
{
    this->decay = ms;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->decay(ms);
    }
}

void ElectSynth::setSustain(float level)
{
    this->sustain = level;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->sustain(level);
    }
}

void ElectSynth::setRelease(float ms)
{
    this->release = ms;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->release(ms);
    }
}

short ElectSynth::getVCO1Table() {
    return this->vco1Table;
}   

short ElectSynth::getVCO2Table() {
    return this->vco2Table;
}

float ElectSynth::getVCORatio() {
    return this->vcoRatio;
}

float ElectSynth::getVCOMix() {
    return this->vcoMix;
}
