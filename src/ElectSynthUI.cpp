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
    display.setCursor(0, 0);
    display.print("ElectSynth");
    display.setCursor(104, 0);
    display.print("VCOs");

    digitalWrite(enc1LED, HIGH);
    digitalWrite(enc2LED, HIGH);
    digitalWrite(enc3LED, HIGH);
    digitalWrite(enc4LED, HIGH);

    drawScope();
    drawVCOFormSelection();
    drawVCORatio();
    drawVCOMix();
}

void ElectSynthUI::update()
{
    drawScope();
}
void ElectSynthUI::drawScope()
{
    display.fillRect(0, 8, 128, 48, BLACK);

    int y = 0;
    int i = 0;
    for (int x = 0; x < 128; x++)
    {
        y = scope->buffer[i] >> 9;
        if (-24 < y && y < 24)
            display.drawPixel(x, y + 32, PURPLE);
        i += 2;
    }
}

void ElectSynthUI::drawVCOFormSelection()
{
    display.setCursor(0, 58);
    display.setTextColor(RED);
    display.print("VCO1");
    for (int i = 0; i < 4; i++)
    {
        uint16_t color = DARK_GREY;
        if (i == this->synth->getVCO1Table())
        {
            color = RED;
        }

        display.drawBitmap(4, 64 + i * 16, WAVEFORM_ICONS[i], 16, 16, color);
    }

    display.setCursor(36, 58);
    display.setTextColor(GREEN);
    display.print("VCO2");
    for (int i = 0; i < 4; i++)
    {
        uint16_t color = DARK_GREY;
        if (i == this->synth->getVCO2Table())
        {
            color = GREEN;
        }

        display.drawBitmap(40, 64 + i * 16, WAVEFORM_ICONS[i], 16, 16, color);
    }
}

void ElectSynthUI::drawVCORatio()
{
    display.setCursor(77, 58);
    display.setTextColor(BLUE);
    display.print("Ratio");

    display.fillRect(77, 68, 30, 12, BLACK);
    display.setTextColor(BLUE);
    display.setCursor(77, 68);
    display.println(synth->getVCORatio(), 3);
    display.drawFastHLine(89 + 6 * vcoAddMod, 78, 6, BLUE);
}

void ElectSynthUI::drawVCOMix()
{
    display.setCursor(83, 96);
    display.setTextColor(YELLOW);
    display.print("Mix");

    display.fillRect(77, 104, 30, 12, BLACK);
    display.setTextColor(YELLOW);
    display.setCursor(77, 104);
    display.println(synth->getVCOMix(), 3);
    display.drawFastHLine(89 + 6 * vcoMixMod, 112, 6, YELLOW);
}

void ElectSynthUI::encoderEvent(int encoder, bool moved_left)
{
    switch (encoder)
    {
    case 0:
    case 1:
    {

        short form = this->synth->getVCOTable(encoder);
        form = moved_left ? form - 1 : form + 1;
        if (form < 0)
        {
            form = 3;
        }
        if (form > 3)
        {
            form = 0;
        }
        this->synth->setVCOTable(encoder, form);
        this->drawVCOFormSelection();
        break;
    }
    case 2:
    {
        float to_add = moved_left ? -vcoAddModes[vcoAddMod] : vcoAddModes[vcoAddMod];
        float ratio = this->synth->getVCORatio() + to_add;
        this->synth->setVCORatio(ratio);

        drawVCORatio();
        break;
    }
    case 3:
    {
        float to_add = moved_left ? -vcoMixModes[vcoMixMod] : vcoMixModes[vcoMixMod];
        float mix = this->synth->getVCOMix() + to_add;
        this->synth->setVCOMix(mix);

        drawVCOMix();
        break;
    }
    }
}

void ElectSynthUI::encoderButtonEvent(int encoder, bool pressed)
{
    switch (encoder)
    {
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
    case 3:
        if (pressed)
        {
            vcoMixMod++;
            if (vcoMixMod > 2)
            {
                vcoMixMod = 0;
            }
            drawVCOMix();
        }
        break;
    default:
        break;
    }
}
