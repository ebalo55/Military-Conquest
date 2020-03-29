//
// Created by ebalo on 06/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_EVENT_H
#define TD_TOWERDEFENSE_SFML_EVENT_H

#include "Button.h"

class Event {
protected:
    bool active = false;
    Button *button;
public:
    Event(Button *btn) :button(btn) {}
    virtual ~Event() {}
    virtual void callback() = 0;

    virtual void setActiveState(bool value) { active = value; }
};

#endif //TD_TOWERDEFENSE_SFML_EVENT_H
