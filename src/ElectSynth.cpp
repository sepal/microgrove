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
        if (this->voiceStack[i] == 0)
        {
            this->voices[i]->vco1->frequency(vcoFreq);
            this->voices[i]->vco2->frequency(vcoFreq * this->vcoRatio);
            this->voices[i]->env->noteOn();
            this->voices[i]->filterEnv->noteOn();
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
        if (this->voiceStack[i] == vcoFreq)
        {
            this->voices[i]->env->noteOff();
            this->voices[i]->filterEnv->noteOff();
            this->voiceStack[i] = 0;
        }
    }
}

AudioStream *ElectSynth::getOutput()
{
    return this->voiceMixer;
}

void ElectSynth::setVCOTable(uint8_t vco, short table)
{
    if (vco == 0)
    {
        this->setVCO1Table(table);
    }
    else
    {
        this->setVCO2Table(table);
    }
}

void ElectSynth::setVCO1Table(short table)
{
    this->vco1Waveform = table;
    AudioNoInterrupts();
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vco1->begin(vco1Waveform);
    }
    AudioInterrupts();
}

void ElectSynth::setVCO2Table(short table)
{
    this->vco2Waveform = table;
    AudioNoInterrupts();
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vco2->begin(this->vco2Waveform);
    }
    AudioInterrupts();
}

void ElectSynth::setVCORatio(float ratio)
{
    this->vcoRatio = ratio;

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        if (this->voiceStack[i] > 0)
        {
            this->voices[i]->vco2->frequency(this->voiceStack[i] * this->vcoRatio);
        }
    }
}

void ElectSynth::setVCOMix(float mix)
{
    this->vcoMix = constrain(mix, 0.0f, 1.0f);

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->vcoMixer->gain(0, 1.0 * vcoMix);
        this->voices[i]->vcoMixer->gain(1, 1.0 * (1.0f - vcoMix));
    }
}

void ElectSynth::setFilterCutoff(float freq)
{
    this->filterFreq = constrain(freq, 0.0f, 1000.0f);

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->frequency(filterFreq);
    }
}

void ElectSynth::setFilterResonance(float q)
{
    this->filterQ = constrain(q, 0.0f, 5.0f);

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->resonance(this->filterQ);
    }
}

void ElectSynth::setVCFDecay(float ms) {
    this->filterDecay = constrain(ms, 10.0f, 1000.0f);

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filterEnv->decay(this->filterDecay/2);
        this->voices[i]->filterEnv->release(this->filterDecay/2);
    }
}

void ElectSynth::setVCFEnv(float n) {
    this->filterEnv = constrain(n, 0.0f, 7.0f);

    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->filter->octaveControl(this->filterEnv);
    }
}

void ElectSynth::setAttack(float ms)
{
    this->attack = constrain(ms, 0.0f, 500.0f);
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->attack(this->attack);
    }
}

void ElectSynth::setDecay(float ms)
{
    this->decay = constrain(ms, 0.0f, 500.0f);
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->decay(decay);
    }
}

void ElectSynth::setSustain(float level)
{
    this->sustain = constrain(level, 0.0f, 1.0f);
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->sustain(this->sustain);
    }
}

void ElectSynth::setRelease(float ms)
{
    this->release = constrain(ms, 0.0f, 1000.0f);
    
    for (int i = 0; i < ELECT_OSC_MAX_VOICES; i++)
    {
        this->voices[i]->env->release(this->release);
    }
}

short ElectSynth::getVCOTable(uint8_t vco)
{
    if (vco == 0)
    {
        return this->vco1Waveform;
    }
    return this->vco2Waveform;
}

short ElectSynth::getVCO1Table()
{
    return this->vco1Waveform;
}

short ElectSynth::getVCO2Table()
{
    return this->vco2Waveform;
}

float ElectSynth::getVCORatio()
{
    return this->vcoRatio;
}

float ElectSynth::getVCOMix()
{
    return this->vcoMix;
}

float ElectSynth::getFilterCutoff()
{
    return this->filterFreq;
}

float ElectSynth::getFilterResonance()
{
    return this->filterQ;
}

float ElectSynth::getAttack()
{
    return this->attack;
}

float ElectSynth::getDecay()
{
    return this->decay;
}

float ElectSynth::getSustain()
{
    return this->sustain;
}

float ElectSynth::getRelease()
{
    return this->release;
}
float ElectSynth::getVCFDecay()
{
    return this->filterDecay;
}

float ElectSynth:: getVCFEnv()
{
    return this->filterEnv;
}