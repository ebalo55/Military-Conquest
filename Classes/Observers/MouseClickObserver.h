//
// Created by ebalo on 18/03/20.
//

#ifndef TD_TOWERDEFENSE_MOUSECLICKOBSERVER_H
#define TD_TOWERDEFENSE_MOUSECLICKOBSERVER_H

#include <SFML/Window.hpp>
#include "../Interface/Event.h"
#include "../Interface/MouseObserver.h"
#include "../Interface/Button.h"
#include "../States/ObserversTypeId.h"

class MouseClickObserver : public MouseObserver {
private:
    Event *event;
    Button *button;
    sf::Window *window;
    OBSERVERS_TYPE_ID click_type;
public:
    MouseClickObserver(Button *button, Event *event, sf::Window *window, OBSERVERS_TYPE_ID click_type = OBSERVERS_TYPE_ID::mouse_click_left) :event(event), button(button), window(window), click_type(click_type) {
        button->registerObserver(click_type, this);
    }

    void update(OBSERVERS_TYPE_ID ev_type) {
        if(ev_type == click_type && button->hasMouseHover(window)) {
            event->callback();
        }
    }
};

#endif //TD_TOWERDEFENSE_MOUSECLICKOBSERVER_H
