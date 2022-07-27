#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <NoteReceiver.h>
#include "input_handler.h"


class Keyboard: public KeyboardHandler, public UtilityButtonHandler
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

            if (pressed) {
                this->receiver->onNoteOn(note, 100);
                usbMIDI.sendNoteOn(note, 100, 0);
            } else {
                this->receiver->onNoteOff(note);
                usbMIDI.sendNoteOff(note, 0, 0);
            }
        }
    }
    virtual void buttonEvent(int button, bool pressed)
    {
        if (!pressed) {
            return;
        }

        switch (button)
        {
        case 4:
            octave = constrain(octave-1, 1, 7);
            break;
        case 7:
            octave = constrain(octave+1, 1, 7);
            break;
        
        default:
            break;
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
