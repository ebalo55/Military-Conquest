//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_CRAFTTURRETBUTTONCLICK_H
#define TD_TOWERDEFENSE_SFML_CRAFTTURRETBUTTONCLICK_H

#include "../Interface/Event.h"
#include "../Elements/TurretGenerator.h"
#include "../Observers/MouseMotionObserver.h"
#include "TurretPositioning.h"

class CraftTurretButtonClickEvent : public Event {
private:
    TurretGenerator *generator;
    bool active = false;
    int turret_index;
    sf::RenderWindow *window;
public:
    CraftTurretButtonClickEvent(Button *btn, sf::RenderWindow *window, TurretGenerator *generator, int turret_index) : Event(btn), generator(generator), turret_index(turret_index), window(window) {}

    void callback() {
        EventHandler *event_handler = generator->getEventHandler();
        if(!active) {
            generator->setTurretPlacement(true);
            new MouseMotionObserver(event_handler, new TurretPositioningEvent(window, generator, turret_index), window, generator);
            active = true;
        }
        else {
            generator->destroyCraftedTurretSprite();
            generator->setTurretPlacement(false);
            active = false;
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_CRAFTTURRETBUTTONCLICK_H
