//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_TURRETPOSITIONING_H
#define TD_TOWERDEFENSE_SFML_TURRETPOSITIONING_H

#include <SFML/Graphics.hpp>
#include "../Interface/Event.h"
#include "../Interface/FakeButton.h"
#include "../Elements/TurretGenerator.h"

class TurretPositioningEvent : public Event {
private:
    sf::Sprite *sprite;
    sf::RenderWindow *window;
public:
    TurretPositioningEvent(sf::RenderWindow *window, TurretGenerator *turret_generator, int turret_index, Button *btn = new FakeButton()) : Event(btn), window(window) {
        sprite = turret_generator->cloneTurretSprite(turret_index);
    }
    ~TurretPositioningEvent() {
        delete sprite;
    }

    void callback() {
        sprite->setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
        window->draw(*sprite);
    }
};

#endif //TD_TOWERDEFENSE_SFML_TURRETPOSITIONING_H
