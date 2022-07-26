#include "ElectSynthUI.h"

ElectSynthUI::ElectSynthUI(ElectSynth *synth)
{
    this->synth = synth;
    this->scope = new AudioAnalyzeOscilloscope();

    this->connection = new AudioConnection(*this->synth->getOutput(), *this->scope);
}

void ElectSynthUI::draw()
{
    display.fillScreen(BLACK);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(20, 0);
    display.print("-ElectSynth-");

    drawVCOFormSelection(0, 10, RED, this->synth->getVCO1Table());
    digitalWrite(enc1LED, HIGH);

    drawVCOFormSelection(0, 70, GREEN, this->synth->getVCO2Table());
    digitalWrite(enc2LED, HIGH);
    digitalWrite(enc3LED, HIGH);
    digitalWrite(enc4LED, HIGH);

    display.drawFastVLine(18, 10, 118, WHITE);
    display.drawFastHLine(0, 68, 128, WHITE);
    display.drawFastVLine(74, 68, 60, WHITE);

    drawScope();
    drawVCORatio();
}

void ElectSynthUI::update()
{
    drawScope();
}

void ElectSynthUI::drawVCOFormSelection(int16_t x, int16_t y, uint16_t active_color, short form)
{
    int colors[] = {DARK_GREY, DARK_GREY, DARK_GREY};
    colors[form] = active_color;
    display.drawBitmap(0, y, ICON_SINE, 16, 16, colors[0]);
    display.drawBitmap(0, y + 20, ICON_SAWTOOTH, 16, 16, colors[1]);
    display.drawBitmap(0, y + 40, ICON_SQUARE, 16, 16, colors[2]);
}

void ElectSynthUI::drawScope()
{
    display.fillRect(20, 10, 118, 57, BLACK);

    int y = 0;
    int i = 0;
    for (int x = 0; x < 108; x++)
    {
        y = scope->buffer[i] >> 8;
        display.drawPixel(x + 20, y + 40, PURPLE);
        i += 2;
    }
}

void ElectSynthUI::drawVCORatio()
{
    int top = 98 - synth->getVCORatio() * 15;
    int bottom = 98 + synth->getVCORatio() * 15;
    display.fillRect(20, 69, 53, 59, BLACK);
    display.drawCircle(46, top, 5, RED);
    display.drawCircle(46, bottom, 5, GREEN);
    display.drawFastVLine(46, top, bottom - top, BLUE);
}

void ElectSynthUI::drawVCOMix()
{
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
        return WAVEFORM_SQUARE;
    }
}

short ElectSynthUI::getNextWaveform(short table)
{
    switch (table)
    {
    case WAVEFORM_SINE:
        return WAVEFORM_SAWTOOTH;
    case WAVEFORM_SAWTOOTH:
        return WAVEFORM_SQUARE;
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
        this->drawVCOFormSelection(0, 10, RED, form);
        break;
    }
    case 1:
    {

        short form = this->synth->getVCO2Table();
        form = moved_left ? getPrevWaveform(form) : getNextWaveform(form);
        this->synth->setVCO2Table(form);
        this->drawVCOFormSelection(0, 70, GREEN, form);
        break;
    }
    case 2:
    {
        float to_add = moved_left ? -0.01f : +0.01f;
        float ratio = this->synth->getVCORatio() + to_add;
        this->synth->setVCORatio(ratio);
        Serial.print("ratio: ");
        Serial.println(ratio);
        drawVCORatio();
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
