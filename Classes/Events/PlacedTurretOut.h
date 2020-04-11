//
// Created by ebalo on 25/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_PLACEDTURRETOUT_H
#define TD_TOWERDEFENSE_SFML_PLACEDTURRETOUT_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Interface/Event.h"
#include "../Elements/Turret.h"
#include "../Elements/TurretGenerator.h"

class PlacedTurretOutEvent : public Event {
private:
    std::shared_ptr<Turret> turret;
    TurretGenerator *generator;
    std::shared_ptr<sf::RenderWindow> window;
    std::string name;
public:
    PlacedTurretOutEvent(std::shared_ptr<Button> btn, std::shared_ptr<sf::RenderWindow> window, TurretGenerator *generator, std::shared_ptr<Turret> turret, int x, int y)
        :Event(btn), window(window), generator(generator), turret(turret) {
        std::stringstream stringstream;
        stringstream << turret->getTurretName() << "-" << x << "x" << y;
        name = stringstream.str();
    }

    void callback() {
        // Recursively remove all the elements of the hover/click event
        for(std::string std :  {"a" + name + "-level", "a" + name + "-power", "a" + name + "-fire-rate", "a" + name + "-upgrade-cost", name + "-rect", name + "-upgrade", name +"turret-radius-overlay"}) {
            generator->deleteDrawable(std);
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_PLACEDTURRETOUT_H
