//
// Created by ebalo on 06/03/20.
//

#ifndef EXAM_EVENT_H
#define EXAM_EVENT_H

#include "Button.h"

class Event {
private:
    Button *button;
public:
    Event(Button *btn) :button(btn) {}
    virtual ~Event() {}
    virtual void callback() = 0;
};

#endif //EXAM_EVENT_H
