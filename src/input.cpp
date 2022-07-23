#include "input.h"

#include <Wire.h>

void Input::begin()
{
    Wire.begin();
}

void Input::setKeyboardHandler(KeyboardHandler *handler)
{
    this->keyboardHandler = handler;
}

void Input::setPadHandler(PadHandler *handler)
{
    this->padHandler = handler;
}

void Input::setUtilityButtonHandler(UtilityButtonHandler *handler)
{
    this->utilityButtonHandler = handler;
}

void Input::setEncoderHandler(EncoderHandler *handler)
{
    this->encoderHandler = handler;
}

void Input::setMenuButtonHandler(MenuButtonHandler *handler)
{
    this->menuButtonHandler = handler;
}

void Input::update()
{
    this->readData();

    // Check updates on menu buttons
    for (int i = 0; i < 3; i++)
    {
        if (bitRead(buttonStates[5], Input::MENU_BIT_MAPPING[i]) != bitRead(lastButtonStates[5], Input::MENU_BIT_MAPPING[i]))
        {
            updateMenu(i, bitRead(buttonStates[5], Input::MENU_BIT_MAPPING[i]));
        }
    }

    // Check keyboard updates.
    for (int i = 0; i < 24; i++)
    {
        if (bitRead(buttonStates[KEYBOARD_BYTE_MAPPING[i]], KEYBOARD_BIT_MAPPING[i]) != bitRead(lastButtonStates[KEYBOARD_BYTE_MAPPING[i]], KEYBOARD_BIT_MAPPING[i]))
        {
            updateKeyboard(i, bitRead(buttonStates[KEYBOARD_BYTE_MAPPING[i]], KEYBOARD_BIT_MAPPING[i]));
        }
    }

    // Update pads.
    for (int i = 0; i < 12; i++)
    {
        if (bitRead(buttonStates[PAD_BYTE_MAPPING[i]], PAD_BIT_MAPPING[i]) != bitRead(lastButtonStates[PAD_BYTE_MAPPING[i]], PAD_BIT_MAPPING[i]))
        {
            updatePad(i, bitRead(buttonStates[PAD_BYTE_MAPPING[i]], PAD_BIT_MAPPING[i]));
        }
    }

    // Update utility buttons.
    for (int i = 0; i < 8; i++)
    {
        if (bitRead(buttonStates[UTILITY_BYTE_MAPPING[i]], UTILITY_BIT_MAPPING[i]) != bitRead(lastButtonStates[UTILITY_BYTE_MAPPING[i]], UTILITY_BIT_MAPPING[i]))
        {
            updateUtility(i, bitRead(buttonStates[UTILITY_BYTE_MAPPING[i]], UTILITY_BIT_MAPPING[i]));
        }
    }

    // Update encoder buttons.
    for (int i = 0; i < 4; i++)
    {
        if (bitRead(buttonStates[6], ENCODER_BIT_MAPPING[i]) != bitRead(lastButtonStates[6], ENCODER_BIT_MAPPING[i]))
        {
            updateEncoderButton(i, bitRead(buttonStates[6], ENCODER_BIT_MAPPING[i]));
        }
    }

    // Update encoders.
    if (lastButtonStates[7] != buttonStates[7])
    {
        for (int i = 0; i < 4; i++)
        {
            byte mask = B00000011;
            mask = mask << i * 2;
            byte enc_val = buttonStates[7] & mask;
            enc_val = enc_val >> i * 2;
            if (enc_val == 2)
            {
                updateEncoder(i, true);
            }
            else if (enc_val == 1)
            {
                updateEncoder(i, false);
            }
        }
    }
}

void Input::readData()
{
    Wire.requestFrom(9, 8);
    lastButtonStates[0] = buttonStates[0];
    lastButtonStates[1] = buttonStates[1];
    lastButtonStates[2] = buttonStates[2];
    lastButtonStates[3] = buttonStates[3];
    lastButtonStates[4] = buttonStates[4];
    lastButtonStates[5] = buttonStates[5];
    lastButtonStates[6] = buttonStates[6];
    lastButtonStates[7] = buttonStates[7];

    while (Wire.available())
    {

        buttonStates[0] = Wire.read();
        buttonStates[1] = Wire.read();
        buttonStates[2] = Wire.read();
        buttonStates[3] = Wire.read();
        buttonStates[4] = Wire.read();
        buttonStates[5] = Wire.read();
        buttonStates[6] = Wire.read();
        buttonStates[7] = Wire.read();
    }
}

void Input::updateMenu(MenuButtonHandler::BUTTONS button, bool pressed)
{
    if (this->menuButtonHandler)
    {
        this->menuButtonHandler->menuButtonEvent(button, pressed);
    }
}

void Input::updateKeyboard(int button, bool pressed)
{
    this->keyboardHandler->keyboardEvent(button, pressed);
}

void Input::updatePad(int pad, bool pressed)
{
    if (this->padHandler)
    {
        this->padHandler->padEvent(pad, pressed);
    }
}

void Input::updateUtility(int key, bool pressed)
{
    if (this->utilityButtonHandler)
    {
        this->utilityButtonHandler->buttonEvent(key, pressed);
    }
}

void Input::updateEncoderButton(int encoder, bool pressed)
{
    if (this->encoderHandler)
    {
        this->encoderHandler->encoderButtonEvent(encoder, pressed);
    }
}

void Input::updateEncoder(int encoder, bool moved_left)
{
    if (this->encoderHandler)
    {
        this->encoderHandler->encoderEvent(encoder, moved_left);
    }
}