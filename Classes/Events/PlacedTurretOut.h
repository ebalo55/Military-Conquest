//
// Created by ebalo on 25/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_PLACEDTURRETOUT_H
#define TD_TOWERDEFENSE_SFML_PLACEDTURRETOUT_H

#include <SFML/Graphics.hpp>
#include "../Interface/Event.h"
#include "../Elements/Turret.h"
#include "../Elements/TurretGenerator.h"

class PlacedTurretOutEvent : public Event {
private:
    Turret *turret;
    TurretGenerator *generator;
    sf::RenderWindow *window;
    std::string name;
public:
    PlacedTurretOutEvent(Button *btn, sf::RenderWindow *window, TurretGenerator *generator, Turret *turret, int x, int y) : Event(btn), window(window), generator(generator), turret(turret) {
        std::stringstream stringstream;
        stringstream << turret->getTurretName() << "-" << x << "x" << y;
        name = stringstream.str();
    }

    void callback() {
        generator->deleteDrawable("a" + name + "-level");
        generator->deleteDrawable("a" + name + "-power");
        generator->deleteDrawable("a" + name + "-fire-rate");
        generator->deleteDrawable("a" + name + "-upgrade-cost");
        generator->deleteDrawable(name + "-rect");
        generator->deleteDrawable(name + "-radius-circle");
    }
};

#endif //TD_TOWERDEFENSE_SFML_PLACEDTURRETOUT_H
