//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_FAKEBUTTON_H
#define TD_TOWERDEFENSE_SFML_FAKEBUTTON_H

#include <SFML/Window.hpp>
#include "Notifier.h"
#include "../States/ObserversTypeId.h"
#include "MouseObserver.h"
#include "Button.h"

class FakeButton : public Button {
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {};
public:
    virtual ~FakeButton() = default;
    bool hasMouseHover(sf::Window *window) override {};
    void notify() override {};
    void notify(OBSERVERS_TYPE_ID ev_type) {
        for(std::pair<unsigned long long, Observer *> line : observers) {
            if(ev_type == OBSERVERS_TYPE_ID::mouse_motion && (line.first == OBSERVERS_TYPE_ID::mouse_motion_hover || line.first == OBSERVERS_TYPE_ID::mouse_motion_out)) {
                ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_out);
                ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_hover);
                ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion);
            }
            else if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_hover && line.first == ev_type) { ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_hover); }
            else if(ev_type == OBSERVERS_TYPE_ID::mouse_motion_out && line.first == ev_type) { ((MouseObserver *)line.second)->update(OBSERVERS_TYPE_ID::mouse_motion_out); }
            else { ((MouseObserver *) line.second)->update(ev_type); }
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_FAKEBUTTON_H
