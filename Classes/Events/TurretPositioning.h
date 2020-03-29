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
        /* We don't have to remove the variable "sprite" because following its construction back to the origin:
         *      TurretGenerator::cloneTurretSprite -> DrawableFactory::instantiateSprite -> RenderableMap::initSprite
         *      it is simply a pointer to a standard instance of sf::Sprite which will be deleted on program exit.
         *
            delete sprite;
         */
        sprite->setPosition(-1, -1);
        sprite->setScale(0, 0);
    }

    void callback() {
        sprite->setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
        window->draw(*sprite);
    }
};

#endif //TD_TOWERDEFENSE_SFML_TURRETPOSITIONING_H
