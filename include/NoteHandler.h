#ifndef _NOTE_HANDLER_H_
#define _NOTE_HANDLER_H_

class NoteHandler
{
public:
    void noteOn(int note, int velocity);
    void noteOff(int note);

    virtual void play() = 0;
    virtual void release() = 0;
};

#endif /* _NOTE_HANDLER_H_ */
