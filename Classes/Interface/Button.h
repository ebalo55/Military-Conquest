//
// Created by ebalo on 21/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BUTTON_H
#define TD_TOWERDEFENSE_SFML_BUTTON_H

#include <iostream>
#include <list>
#include "Notifier.h"
#include "../States/ObserversTypeId.h"
#include "MouseObserver.h"

class Button : public sf::Drawable, public sf::Transformable, public Notifier {
protected:
    bool button_was_hover = false,
        state_copy = false;
public:
    virtual bool hasMouseHover(sf::Window *window) = 0;
    bool wasHover() { return button_was_hover; }
    void notify() override {};
    void notify(OBSERVERS_TYPE_ID ev_type) {
        for(std::pair<unsigned long long, Observer *> line : observers) {
            if(ev_type == OBSERVERS_TYPE_ID::mouse_motion && (line.first == OBSERVERS_TYPE_ID::mouse_motion_hover || line.first == OBSERVERS_TYPE_ID::mouse_motion_out)) {
                ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_out);
                ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_hover);
            }
            else if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_hover && line.first == ev_type) { ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_hover); }
            else if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_out && line.first == ev_type) { ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_out); }
            else if((ev_type == OBSERVERS_TYPE_ID::mouse_click_left || ev_type == OBSERVERS_TYPE_ID::mouse_click_right) && line.first == ev_type) { ((MouseObserver *)line.second)->update(ev_type); }
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_BUTTON_H
