#ifndef _NOTE_RECEIVER_H_
#define _NOTE_RECEIVER_H_

class NoteReceiver
{
public:
    virtual void onNoteOn(int note, int velocity);
    virtual void onNoteOff(int note);
};

#endif /* _NOTE_RECEIVER_H_ */
