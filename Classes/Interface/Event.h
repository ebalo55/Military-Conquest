//
// Created by ebalo on 06/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_EVENT_H
#define TD_TOWERDEFENSE_SFML_EVENT_H

#include <memory>
#include "Button.h"

class Event {
protected:
    bool active = false;
    std::shared_ptr<Button> button;
public:
    Event(std::shared_ptr<Button> btn) :button(btn) {}
    virtual ~Event() {}
    virtual void callback() = 0;

    virtual void setActiveState(bool value) { active = value; }
};

#endif //TD_TOWERDEFENSE_SFML_EVENT_H
