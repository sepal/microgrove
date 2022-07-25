#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "input_handler.h"

class NoteReceiver
{
public:
    virtual void onNoteOn(int note, int velocity);
    virtual void onNoteOff(int note);
};


class Keyboard: public KeyboardHandler
{
public:
    Keyboard()
    {
        this->octave = 4;
    }

    virtual void keyboardEvent(int button, bool pressed)
    {
        if (receiver)
        {
            int note = (12 * this->octave) + button;

            if (pressed)
                this->receiver->onNoteOn(note, 100);
            else
                this->receiver->onNoteOff(note);
        }
    }

    virtual void setReceiver(NoteReceiver* receiver)
    {
        this->receiver = receiver;
    }

protected:
    int octave;
    NoteReceiver *receiver;
};

#endif /* _KEYBOARD_H_ */
