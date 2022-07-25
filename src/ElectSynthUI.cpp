#include "ElectSynthUI.h"


ElectSynthUI::ElectSynthUI(ElectSynth *synth) {
    this->synth = synth;
}

void ElectSynthUI::encoderEvent(int encoder, bool moved_left) {
    switch (encoder)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        {
            float to_add = moved_left ? -0.01f : + 0.01f;
            float ratio = this->synth->getVCORatio() + to_add;
            this->synth->setVCORatio(ratio);
            Serial.print("ratio: ");
            Serial.println(ratio);
            break;
        }
    case 3:
        {
            float to_add = moved_left ? -0.1f : + 0.1f;
            float mix = this->synth->getVCOMix() + to_add;
            this->synth->setVCOMix(mix);
            Serial.print("mix: ");
            Serial.println(mix);
            break;
        }
    }
}

void ElectSynthUI::encoderButtonEvent(int encoder, bool pressed) {
    
}
