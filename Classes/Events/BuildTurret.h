//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BUILDTURRET_H
#define TD_TOWERDEFENSE_SFML_BUILDTURRET_H

#include <memory>
#include "../Interface/Event.h"
#include "../Elements/TurretGenerator.h"
#include "PlacedTurretHover.h"
#include "PlacedTurretOut.h"
#include "PlacedTurretClick.h"

class BuildTurretEvent : public Event {
private:
    TurretGenerator *generator;
    int turret_index;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Turret> turret;
    // This is passed as a raw pointer as it is passed from another event using "this"
    Event *sender;
public:
    BuildTurretEvent(std::shared_ptr<Button> btn, std::shared_ptr<sf::RenderWindow> window, TurretGenerator *generator,
                     Event *event)
            : Event(btn), generator(generator), window(window), sender(std::move(event)) {
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
            std::shared_ptr<ButtonRect> btn = std::make_shared<ButtonRect>(ButtonRect(40, 40));
            btn->setPosition(map_x_index * 40, map_y_index * 40);
            generator->getEventHandler()->registerButton(btn);
            new MouseHoverObserver(btn,
                                   std::unique_ptr<Event>(
                                           new PlacedTurretHoverEvent(btn, window, generator, turret, map_x_index * 40,
                                                                      map_y_index * 40)), window);
            new MouseOutObserver(btn, std::unique_ptr<Event>(
                    new PlacedTurretOutEvent(btn, window, generator, turret, map_x_index * 40, map_y_index * 40)),
                                 window);
            new MouseClickObserver(btn,
                                   std::unique_ptr<Event>(
                                           new PlacedTurretClickEvent(btn, window, generator, turret, map_x_index * 40,
                                                                      map_y_index * 40)), window);

            turret->setPosition(sf::Vector2f{(float) (map_x_index * 40 + 20), (float) (map_y_index * 40 + 20)});

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
