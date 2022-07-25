#include "ElectSynthUI.h"

ElectSynthUI::ElectSynthUI(ElectSynth *synth)
{
    this->synth = synth;
}

short ElectSynthUI::getPrevWaveform(short table)
{
    switch (table)
    {
    case WAVEFORM_PULSE:
        return WAVEFORM_SAWTOOTH;
    case WAVEFORM_SAWTOOTH:
        return WAVEFORM_SINE;
    default:
        return WAVEFORM_PULSE;
    }
}

short ElectSynthUI::getNextWaveform(short table)
{
    switch (table)
    {
    case WAVEFORM_SINE:
        return WAVEFORM_SAWTOOTH;
    case WAVEFORM_SAWTOOTH:
        return WAVEFORM_PULSE;
    default:
        return WAVEFORM_SINE;
    }
}

void ElectSynthUI::encoderEvent(int encoder, bool moved_left)
{
    switch (encoder)
    {
    case 0:
    {

        short form = this->synth->getVCO1Table();
        form = moved_left ? getPrevWaveform(form) : getNextWaveform(form);
        this->synth->setVCO1Table(form);
        break;
    }
    case 1:
    {

        short form = this->synth->getVCO2Table();
        form = moved_left ? getPrevWaveform(form) : getNextWaveform(form);
        this->synth->setVCO2Table(form);
        break;
    }
    case 2:
    {
        float to_add = moved_left ? -0.01f : +0.01f;
        float ratio = this->synth->getVCORatio() + to_add;
        this->synth->setVCORatio(ratio);
        Serial.print("ratio: ");
        Serial.println(ratio);
        break;
    }
    case 3:
    {
        float to_add = moved_left ? -0.1f : +0.1f;
        float mix = this->synth->getVCOMix() + to_add;
        this->synth->setVCOMix(mix);
        Serial.print("mix: ");
        Serial.println(mix);
        break;
    }
    }
}

void ElectSynthUI::encoderButtonEvent(int encoder, bool pressed)
{
}
