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

    drawScope();

    switch (page)
    {
    case 0:
        display.setCursor(104, 0);
        display.print("VCOs");
        digitalWrite(enc1LED, HIGH);
        digitalWrite(enc2LED, HIGH);
        digitalWrite(enc3LED, HIGH);
        digitalWrite(enc4LED, HIGH);

        drawVCOFormSelection();
        drawVCORatio();
        drawVCOMix();
        break;
    case 1:
        display.setCursor(110, 0);
        display.print("VCF");
        digitalWrite(enc1LED, HIGH);
        digitalWrite(enc2LED, HIGH);
        digitalWrite(enc3LED, LOW);
        digitalWrite(enc4LED, LOW);

        drawVCFCurve();
        break;
    default:
        break;
    }
}

void ElectSynthUI::update()
{
    drawScope();
}

void ElectSynthUI::encoderEvent(int encoder, bool moved_left)
{
    switch (page)
    {
    case 0:
        this->vcoEncoderEvent(encoder, moved_left);
        break;

    default:
        this->vcfEncoderEvent(encoder, moved_left);
        break;
    }
}

void ElectSynthUI::encoderButtonEvent(int encoder, bool pressed)
{
    switch (page)
    {
    case 0:
        this->vcoEncoderButtonEvent(encoder, pressed);
        break;

    case 1:
        this->vcfEncoderButtonEvent(encoder, pressed);
        break;
    default:
        break;
    }
}

void ElectSynthUI::menuButtonEvent(BUTTONS button, bool pressed)
{
    if (!pressed)
    {
        return;
    }

    switch (button)
    {
    case MenuButtonHandler::LEFT:
        page--;
        if (page < 0)
        {
            page = 1;
        }
        break;
    case MenuButtonHandler::RIGHT:
        page++;
        if (page > 1)
        {
            page = 0;
        }
        break;

    default:
        break;
    }
    draw();
}

void ElectSynthUI::drawScope()
{
    display.fillRect(0, 8, 128, 48, BLACK);

    int y = 0;
    int i = 0;
    for (int x = 0; x < 128; x++)
    {
        y = scope->buffer[i] >> 8;
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

void ElectSynthUI::vcoEncoderEvent(int encoder, bool moved_left)
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

void ElectSynthUI::vcoEncoderButtonEvent(int encoder, bool pressed)
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

void ElectSynthUI::drawVCFCurve()
{
    display.fillRect(0, 58, 64, 70, BLACK);
    display.setTextColor(WHITE);
    display.setCursor(8, 58);
    display.print("Freq/Res");

    display.drawFastVLine(2, 64, 52, RED);
    display.drawFastHLine(4, 118, 52, GREEN);

    int x = ((this->synth->getFilterCutoff() / 1000.0f) * 54.0f);
    int y = 118 - ((this->synth->getFilterResonance() / 5.0f) * 54.0f);

    if (vcfQMode == vcfFreqMode)
    {
        display.drawCircle(x, y, vcfRadius[vcfQMode], WHITE);
    }
    else
    {
        display.drawCircle(x, y, vcfRadius[vcfFreqMode], RED);
        display.drawCircle(x, y, vcfRadius[vcfQMode], GREEN);
    }
}

void ElectSynthUI::vcfEncoderEvent(int encoder, bool moved_left)
{

    switch (encoder)
    {
    case 0:
    {
        float to_add = moved_left ? -vcfFreqModes[vcfFreqMode] : vcfFreqModes[vcfFreqMode];
        float freq = this->synth->getFilterCutoff() + to_add;
        this->synth->setFilterCutoff(freq);
        this->drawVCFCurve();
        break;
    }
    case 1:
    {
        float to_add = moved_left ? -vcfQModes[vcfQMode] : vcfQModes[vcfQMode];
        float q = this->synth->getFilterResonance() + to_add;
        this->synth->setFilterResonance(q);
        this->drawVCFCurve();
        break;
    }

    default:
        break;
    }
}

void ElectSynthUI::vcfEncoderButtonEvent(int encoder, bool pressed)
{
    if (!pressed)
    {
        return;
    }

    switch (encoder)
    {
    case 0:
        vcfFreqMode++;
        if (vcfFreqMode > 2)
            vcfFreqMode = 0;
        this->drawVCFCurve();
        break;
    case 1:
        vcfQMode++;
        if (vcfQMode > 2)
            vcfQMode = 0;
        this->drawVCFCurve();
        break;

    default:
        break;
    }
}