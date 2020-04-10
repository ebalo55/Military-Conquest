//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_MOUSEMOTIONOBSERVER_H
#define TD_TOWERDEFENSE_SFML_MOUSEMOTIONOBSERVER_H

#include <memory>
#include <SFML/Window.hpp>
#include "../Interface/MouseObserver.h"
#include "../Interface/Event.h"
#include "../Interface/Button.h"
#include "../States/MouseStates.h"
#include "../States/ObserversTypeId.h"
#include "../EventHandler.h"
#include "../Elements/TurretGenerator.h"
#include "../Events/BuildTurret.h"

class MouseMotionObserver : public MouseObserver {
private:
    std::shared_ptr<EventHandler> event_handler;
    Event *event,
        *sender;
    std::shared_ptr<FakeButton> button;

    bool kill_switch = false;
public:
    MouseMotionObserver(std::shared_ptr<EventHandler> event_handler, Event *event, Event *sender, std::shared_ptr<sf::RenderWindow> window,
            TurretGenerator& generator, OBSERVERS_TYPE_ID observer_id = OBSERVERS_TYPE_ID::mouse_motion)
        :event_handler(event_handler), event(event), sender(sender) {
        button = std::make_shared<FakeButton>();
        button->registerObserver(observer_id, this);
        new MouseClickObserver(button, new BuildTurretEvent(button, window, generator, sender), window);
        event_handler->registerButton(button);
            generator.setCraftVirtualButton(button);
    }
    ~MouseMotionObserver() {
        button->deleteObserver(OBSERVERS_TYPE_ID::mouse_motion);
        event_handler->addToRemoveList(button);
    }

    void update(OBSERVERS_TYPE_ID ev_type) {
        if(!kill_switch) {
            if(ev_type == OBSERVERS_TYPE_ID::mouse_motion) {
                event->callback();
            }
        }
        else { delete this; }
    }

    void activateKillSwitch() { kill_switch = true; }
};
#endif //TD_TOWERDEFENSE_SFML_MOUSEMOTIONOBSERVER_H
