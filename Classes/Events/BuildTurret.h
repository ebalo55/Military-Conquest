//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BUILDTURRET_H
#define TD_TOWERDEFENSE_SFML_BUILDTURRET_H

#include "../Interface/Event.h"
#include "../Elements/TurretGenerator.h"
#include "PlacedTurretHover.h"
#include "PlacedTurretOut.h"
#include "PlacedTurretClick.h"

class BuildTurretEvent : public Event {
private:
    TurretGenerator *generator;
    int turret_index;
    sf::RenderWindow *window;
    Turret *turret;
    Event *sender;
public:
    BuildTurretEvent(Button *btn, sf::RenderWindow *window, TurretGenerator *generator, Event *event) : Event(btn), generator(generator), window(window), sender(event) {
        turret_index = generator->getSelectedTurret();
        turret = generator->generate(turret_index);
    }

    void callback() {
        sf::Vector2i positions = sf::Mouse::getPosition(*window);
        int map_x_index = positions.x / 40,
            map_y_index = positions.y / 40;

        Map *map = generator->getMap();
        int *mutable_map = map->getMap();
        if(mutable_map[map_x_index + map_y_index * map->getMapWidth()] == 4 && turret->getTower()->pay(turret->getCost())) {
            mutable_map[map_x_index + map_y_index * map->getMapWidth()] = 5 + turret_index;

            // Create a virtual button on the turret instance
            ButtonRect *btn = new ButtonRect(40, 40);
            btn->setPosition(map_x_index * 40, map_y_index * 40);
            generator->getEventHandler()->registerButton(btn);
            new MouseHoverObserver(btn, new PlacedTurretHoverEvent(btn, window, generator, turret, generator->getFont(), map_x_index * 40, map_y_index * 40), window);
            new MouseOutObserver(btn, new PlacedTurretOutEvent(btn, window, generator, turret, map_x_index * 40, map_y_index * 40), window);
            new MouseClickObserver(btn, new PlacedTurretClickEvent(btn, window, generator, turret, generator->getFont(), map_x_index * 40, map_y_index * 40), window);

            // Clear the turret placement loop variables
            generator->destroyCraftedTurretSprite();
            generator->setTurretPlacement(false);
            generator->getEventHandler()->addToRemoveList(button);
            generator->registerTurret(turret);

            sender->setActiveState(false);
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_BUILDTURRET_H
