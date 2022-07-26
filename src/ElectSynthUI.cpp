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

    drawVCOFormSelection();
    digitalWrite(enc1LED, HIGH);

    digitalWrite(enc2LED, HIGH);
    digitalWrite(enc3LED, HIGH);
    digitalWrite(enc4LED, HIGH);

    display.drawFastVLine(18, 10, 118, WHITE);
    display.drawFastHLine(20, 68, 108, WHITE);
    display.drawFastVLine(74, 68, 60, WHITE);

    drawScope();
    drawVCORatio();
    drawVCOMix();
}

void ElectSynthUI::update()
{
    drawScope();
}

void ElectSynthUI::drawVCOFormSelection()
{
    display.setCursor(0, 0);
    display.print("O");
    display.print(vcoTableSelect+1);
    for (int i = 0; i < 4; i++)
    {
        uint16_t color = DARK_GREY;
        if (i == this->synth->getVCO1Table())
        {
            color = CYAN;
        }
        if (i == this->synth->getVCO2Table())
        {
            color = MAGENTA;
        }

        display.drawBitmap(0, 10 + i * 16, WAVEFORM_ICONS[i], 16, 16, color);
    }
}

void ElectSynthUI::drawScope()
{
    display.fillRect(20, 10, 118, 57, BLACK);

    int y = 0;
    int i = 0;
    for (int x = 0; x < 108; x++)
    {
        y = scope->buffer[i] >> 8;
        if (y < 23)
            display.drawPixel(x + 20, y + 40, PURPLE);
        i += 2;
    }
}

void ElectSynthUI::drawVCORatio()
{
    display.fillRect(20, 69, 53, 59, BLACK);
    display.setTextColor(BLUE);
    display.setCursor(30, 98);
    display.println(synth->getVCORatio(), 3);
    display.drawFastHLine(42 + 6 * vcoAddMod, 106, 6, BLUE);
}

void ElectSynthUI::drawVCOMix()
{
    display.fillRect(75, 69, 53, 59, BLACK);
    display.drawCircle(101, 98 - 15, 5, RED);
    display.drawCircle(101, 98 + 15, 5, GREEN);
    display.fillCircle(101, 113 - synth->getVCOMix() * 30, 3, YELLOW);
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

        short form = this->synth->getVCOTable(vcoTableSelect);
        form = moved_left ? form - 1 : form + 1;
        if (form < 0)
        {
            form = 3;
        }
        if (form > 3)
        {
            form = 0;
        }
        this->synth->setVCOTable(vcoTableSelect, form);
        this->drawVCOFormSelection();
        break;
    }
    case 1:
    {

        break;
    }
    case 2:
    {
        float to_add = moved_left ? -vcoAddModes[vcoAddMod] : vcoAddModes[vcoAddMod];
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
        drawVCOMix();
        break;
    }
    }
}

void ElectSynthUI::encoderButtonEvent(int encoder, bool pressed)
{
    switch (encoder)
    {
    case 0:
        if (pressed)
        {
            vcoTableSelect = vcoTableSelect == 0 ? 1 : 0;
            Serial.println(vcoTableSelect);
        }
        break;
    case 2:
        if (pressed)
        {
            vcoAddMod++;
            if (vcoAddMod > 2)
            {
                vcoAddMod = 0;
            }
            drawVCORatio();
        }
        break;

    default:
        break;
    }
}
