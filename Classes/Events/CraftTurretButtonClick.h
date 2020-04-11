//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_CRAFTTURRETBUTTONCLICK_H
#define TD_TOWERDEFENSE_SFML_CRAFTTURRETBUTTONCLICK_H

#include <memory>
#include "../Interface/Event.h"
#include "../Elements/TurretGenerator.h"
#include "../Observers/MouseMotionObserver.h"
#include "TurretPositioning.h"

class CraftTurretButtonClickEvent : public Event {
private:
    TurretGenerator *generator;
    int turret_index;
    std::shared_ptr<sf::RenderWindow> window;
    MouseMotionObserver *motion_observer;
public:
    CraftTurretButtonClickEvent(std::shared_ptr<Button> btn, std::shared_ptr<sf::RenderWindow> window, TurretGenerator *generator, int turret_index)
            :Event(btn), generator(generator), turret_index(turret_index), window(window) {
        active = false;
    }

    void callback() {
        if(!active) {
            generator->setTurretPlacement(true);
            motion_observer = new MouseMotionObserver(generator->getEventHandler(),
                    new TurretPositioningEvent(window, generator, turret_index), this, window, generator);
            active = true;
        }
        else {
            setActiveState(false);
            motion_observer->activateKillSwitch();
        }
    }

    void setActiveState(bool state) override {
        generator->setTurretPlacement(false);
        active = false;
        generator->destroyCraftedTurretSprite();
    }
};

#endif //TD_TOWERDEFENSE_SFML_CRAFTTURRETBUTTONCLICK_H
