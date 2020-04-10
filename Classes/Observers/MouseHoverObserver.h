//
// Created by ebalo on 18/03/20.
//

#ifndef TD_TOWERDEFENSE_MOUSEHOVEROBSERVER_H
#define TD_TOWERDEFENSE_MOUSEHOVEROBSERVER_H

#include <memory>
#include <SFML/Window.hpp>
#include "../Interface/MouseObserver.h"
#include "../Interface/Event.h"
#include "../Interface/Button.h"
#include "../States/MouseStates.h"
#include "../States/ObserversTypeId.h"

class MouseHoverObserver : public MouseObserver {
private:
    Event *event;
    std::shared_ptr<Button> button;
    std::shared_ptr<sf::Window> window;
public:
    MouseHoverObserver(std::shared_ptr<Button> button, Event *event, std::shared_ptr<sf::Window> window) :event(event), button(button), window(window) {
        button->registerObserver(OBSERVERS_TYPE_ID::mouse_motion_hover, this);
    }
    ~MouseHoverObserver() {
        delete event;
    }

    void update(OBSERVERS_TYPE_ID ev_type) {
        if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_hover && button->hasMouseHover(window.get())) {
            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Hand);
            window->setMouseCursor(cursor);
            event->callback();
        }
    }
};

#endif //TD_TOWERDEFENSE_MOUSEHOVEROBSERVER_H