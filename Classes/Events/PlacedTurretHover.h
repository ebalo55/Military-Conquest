//
// Created by ebalo on 25/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_PLACEDTURRETHOVER_H
#define TD_TOWERDEFENSE_SFML_PLACEDTURRETHOVER_H

#include <SFML/Graphics.hpp>
#include <zconf.h>
#include "../Interface/Event.h"
#include "../Elements/Turret.h"
#include "../Elements/TurretGenerator.h"

class PlacedTurretHoverEvent : public Event {
private:
    sf::RectangleShape rect;
    sf::Text level,
        power,
        fire_rate,
        upgrade_cost;
    sf::CircleShape radius_circle;

    Turret *turret;
    TurretGenerator *generator;
    sf::RenderWindow *window;
    sf::Font *font;
    std::string name;

    DrawableFactory factory;

    std::stringstream stringstream;
public:
    PlacedTurretHoverEvent(Button *btn, sf::RenderWindow *window, TurretGenerator *generator, Turret *turret, sf::Font *font, int x, int y) : Event(btn), window(window), generator(generator), font(font), turret(turret) {
        factory.setWindow(window);
        factory.setEventHandler(generator->getEventHandler());

        font = generator->getFont();

        stringstream << turret->getTurretName() << "-" << x << "x" << y;
        name = stringstream.str();

        int position_x = x +100 > WINDOW_WIDTH ? x -80 : x,
            position_y = y -80 > 0 ? y -80 : y +60;
        sf::Color color(0xcc, 0xcc, 0xcc);

        rect.setPosition(position_x, position_y);
        rect.setSize(sf::Vector2f {100, 80});
        rect.setFillColor(sf::Color(0, 0, 0, 0xbb));

        level.setFont(*font);
        level.setPosition(sf::Vector2f {(float)(position_x +5), (float)(position_y +5)});
        level.setCharacterSize(10);
        level.setStyle(sf::Text::Style::Bold);
        level.setFillColor(color);
        power.setFont(*font);
        power.setPosition(sf::Vector2f {(float)(position_x +5), (float)(position_y +20)});
        power.setCharacterSize(10);
        power.setFillColor(color);
        fire_rate.setFont(*font);
        fire_rate.setPosition(sf::Vector2f {(float)(position_x +5), (float)(position_y +35)});
        fire_rate.setCharacterSize(10);
        fire_rate.setFillColor(color);
        upgrade_cost.setFont(*font);
        upgrade_cost.setPosition(sf::Vector2f {(float)(position_x +5), (float)(position_y +50)});
        upgrade_cost.setCharacterSize(10);
        upgrade_cost.setFillColor(color);

        int rad = turret->getRadius();
        radius_circle.setOrigin(sf::Vector2f {(float)(rad), (float)(rad)});
        radius_circle.setPosition(sf::Vector2f {(float)(x +20), (float)(y +20)});
        radius_circle.setRadius(rad);
        radius_circle.setFillColor(sf::Color(0x68, 0xac, 0x82, 0x55));
        radius_circle.setOutlineColor(sf::Color(0x6e, 0xa0, 0x70, 0x88));
        radius_circle.setOutlineThickness(2);
    }

    void callback() {
        generator->registerDrawable("a" + name + "-level", &level);
        generator->registerDrawable("a" + name + "-power", &power);
        generator->registerDrawable("a" + name + "-fire-rate", &fire_rate);
        generator->registerDrawable("a" + name + "-upgrade-cost", &upgrade_cost);
        generator->registerDrawable(name + "-rect", &rect);
        generator->registerDrawable(name + "-radius-circle", &radius_circle);

        stringstream.str("");
        stringstream << "Level " << turret->getLevel();
        level.setString(stringstream.str());

        stringstream.str("");
        stringstream << "Power: " << turret->getPower();
        power.setString(stringstream.str());

        stringstream.str("");
        stringstream << "Fire rate: " << turret->getFireRate();
        fire_rate.setString(stringstream.str());

        stringstream.str("");
        stringstream << "Upgrade cost: " << turret->getUpgradeCost();
        upgrade_cost.setString(stringstream.str());
    }
};

#endif //TD_TOWERDEFENSE_SFML_PLACEDTURRETHOVER_H
