#ifndef _INPUT_H_
#define _INPUT_H_

#include <Arduino.h>
#include "input_handler.h"

class Input
{
public:
    void begin();

    void update();

    void setKeyboardHandler(KeyboardHandler *handler);
    void setPadHandler(PadHandler *handler);
    void setUtilityButtonHandler(UtilityButtonHandler *handler);
    void setEncoderHandler(EncoderHandler *handler);
    void setMenuButtonHandler(MenuButtonHandler *handler);

private:
    void readData();

    void updateKeyboard(int button, bool pressed);
    void updatePad(int pad, bool pressed);
    void updateMenu(MenuButtonHandler::BUTTONS button, bool pressed);
    void updateUtility(int key, bool pressed);
    void updateEncoderButton(int encoder, bool pressed);
    void updateEncoder(int encoder, bool moved_left);

    byte buttonStates[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    byte lastButtonStates[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    const byte MENU_BIT_MAPPING[3] = {5, 4, 6};

    KeyboardHandler *keyboardHandler;
    PadHandler *padHandler;
    UtilityButtonHandler *utilityButtonHandler;
    EncoderHandler *encoderHandler;
    MenuButtonHandler *menuButtonHandler;

    const byte KEYBOARD_BYTE_MAPPING[24] = {
        3, // SW25
        2, // SW18
        3, // SW26
        2, // SW19
        3, // SW27
        3, // SW28
        2, // SW20
        4, // SW36
        2, // SW21
        4, // SW37
        3, // SW29
        4, // SW38
        4, // SW39
        3, // SW30
        4, // SW40
        3, // SW31
        5, // SW41
        5, // SW42
        3, // SW32
        4, // SW35
        4, // SW33
        5, // SW43
        3, // SW34
        5, // SW44
    };

    const byte KEYBOARD_BIT_MAPPING[24] = {
        0, // SW25
        1, // SW18
        1, // SW26
        2, // SW19
        2, // SW27
        3, // SW28
        3, // SW20
        3, // SW36
        4, // SW21
        4, // SW37
        4, // SW29
        5, // SW38
        6, // SW39
        5, // SW30
        7, // SW40
        6, // SW31
        0, // SW41
        1, // SW42
        7, // SW32
        2, // SW35
        0, // SW33
        2, // SW43
        1, // SW34
        3, // SW44
    };

    const byte PAD_BYTE_MAPPING[12] = {
        0, // SW1
        0, // SW2
        0, // SW3
        0, // SW8
        1, // SW9
        1, // SW10
        1, // SW15
        1, // SW16
        2, // SW17
        2, // SW22
        2, // SW23
        2, // SW24
    };

    const byte PAD_BIT_MAPPING[12] = {
        9, // SW1
        1, // SW2
        2, // SW3
        7, // SW8
        0, // SW9
        1, // SW10
        6, // SW15
        7, // SW16
        0, // SW17
        5, // SW22
        6, // SW23
        7, // SW24
    };

    const byte UTILITY_BYTE_MAPPING[8] = {
        0, // SW4
        0, // SW5
        0, // SW6
        0, // SW7
        1, // SW11
        1, // SW12
        1, // SW13
        1, // SW14
    };

    const byte UTILITY_BIT_MAPPING[8] = {
        3, // SW4
        4, // SW5
        5, // SW6
        6, // SW7
        2, // SW11
        3, // SW12
        4, // SW13
        5, // SW14
    };

    const byte ENCODER_BIT_MAPPING[4] = {
        0,
        1,
        2,
        3,
    };
};

#endif /* _INPUT_H_ */
