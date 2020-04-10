//
// Created by ebalo on 18/03/20.
//

#ifndef TD_TOWERDEFENSE_MOUSEOUTOBSERVER_H
#define TD_TOWERDEFENSE_MOUSEOUTOBSERVER_H

#include <memory>
#include <SFML/Window.hpp>
#include "../Interface/MouseObserver.h"
#include "../Interface/Event.h"
#include "../Interface/Button.h"

class MouseOutObserver : public MouseObserver {
private:
    std::shared_ptr<Button> btn;
    std::shared_ptr<sf::Window> window;
    Event *event;
public:
    MouseOutObserver(std::shared_ptr<Button> btn, Event *event, std::shared_ptr<sf::Window> window) :btn(btn), event(event), window(window) {
        btn->registerObserver(OBSERVERS_TYPE_ID::mouse_motion_out, this);
    }

    void update(OBSERVERS_TYPE_ID ev_type) {
        if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_out && btn->wasHover() && !btn->hasMouseHover(window.get())) {
            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window->setMouseCursor(cursor);
            event->callback();
        }
    }
};

#endif //TD_TOWERDEFENSE_MOUSEOUTOBSERVER_H
