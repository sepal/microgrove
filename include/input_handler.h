#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

class KeyboardHandler
{
public:
    virtual void keyboardEvent(int button, bool pressed);
};

class PadHandler
{
public:
    virtual void padEvent(int pad, bool pressed);
};

class UtilityButtonHandler
{
public:
    virtual void buttonEvent(int button, bool pressed);
};

class EncoderHandler
{
public:
    virtual void encoderEvent(int encoder, bool moved_left);
    virtual void encoderButtonEvent(int encoder, bool pressed);
};

class MenuButtonHandler
{
public:
    enum BUTTONS
    {
        MAIN,
        LEFT,
        RIGHT,
    };

    virtual void menuButtonEvent(BUTTONS button, bool pressed);
};

#endif /* _INPUT_HANDLER_H_ */
