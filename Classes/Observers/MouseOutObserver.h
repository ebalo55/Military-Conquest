//
// Created by ebalo on 18/03/20.
//

#ifndef TD_TOWERDEFENSE_MOUSEOUTOBSERVER_H
#define TD_TOWERDEFENSE_MOUSEOUTOBSERVER_H

#include <SFML/Window.hpp>
#include "../Interface/MouseObserver.h"
#include "../Interface/Event.h"
#include "../Interface/Button.h"

class MouseOutObserver : public MouseObserver {
private:
    Button *btn;
    sf::Window *window;
    Event *event;
public:
    MouseOutObserver(Button *btn, Event *event, sf::Window *window) :btn(btn), event(event), window(window) {
        btn->registerObserver(OBSERVERS_TYPE_ID::mouse_motion_out, this);
    }

    void update(OBSERVERS_TYPE_ID ev_type) {
        if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_out && btn->wasHover() && !btn->hasMouseHover(window)) {
            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window->setMouseCursor(cursor);
            event->callback();
        }
    }
};

#endif //TD_TOWERDEFENSE_MOUSEOUTOBSERVER_H
