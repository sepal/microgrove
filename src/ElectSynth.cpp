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
        this->connections[i] = new AudioConnection(*this->voices[i]->getOutput(), 0, *this->voiceMixer, i);
    }
}

void ElectSynth::onNoteOn(int note, int velocity)
{
    Serial.print("Note on: ");
    Serial.println(note, DEC);
    float freq = NOTE_FREQ[note];
    this->voices[0]->onNoteOn(freq);
}

void ElectSynth::onNoteOff(int note)
{
    this->voices[0]->onNoteOff();
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

void ElectSynth::setVCODetune(float ratio)
{
    this->vcoRatio = ratio;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vcoRatio = ratio;
    }
}

void ElectSynth::setVCOMix(float mix)
{
    this->vcoMix = mix;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vcoMixer->gain(0, 1.0 * mix);
        this->voices[i]->vcoMixer->gain(1, 1.0 * (1.0f - mix));
    }
}

void ElectSynth::setFilterCutoff(float freq)
{
    this->freq = freq;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->frequency(freq);
    }
}

void ElectSynth::setFilterResonance(float q)
{
    this->q = q;
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->resonance(q);
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
