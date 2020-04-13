//
// Created by ebalo on 25/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_PLACEDTURRETHOVER_H
#define TD_TOWERDEFENSE_SFML_PLACEDTURRETHOVER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Interface/Event.h"
#include "../Elements/Turret.h"
#include "../Elements/TurretGenerator.h"

class PlacedTurretHoverEvent : public Event {
private:
    std::shared_ptr<sf::CircleShape> radius_circle;

    std::shared_ptr<Turret> turret;
    TurretGenerator *generator;
    std::shared_ptr<sf::RenderWindow> window;
    sptr<sf::Font> font;
    std::string name;

    DrawableFactory factory;

    std::stringstream stringstream;
public:
    PlacedTurretHoverEvent(std::shared_ptr<Button> btn, std::shared_ptr<sf::RenderWindow> window, TurretGenerator *generator, std::shared_ptr<Turret> turret, int x, int y)
        :Event(btn), window(window), generator(generator), font(generator->getFont()), turret(turret) {
        factory.setWindow(window);
        factory.setEventHandler(generator->getEventHandler());

        stringstream << turret->getTurretName() << "-" << x << "x" << y;
        name = stringstream.str();

        int position_x = x +100 > WINDOW_WIDTH ? x -80 : x,
            position_y = y -80 > 0 ? y -80 : y +60;
        sf::Color color(0xcc, 0xcc, 0xcc);

        factory.instantiateTexture("turret-bg", AssetsMap::get("tower-bg"));
        factory.instantiateSprite("turret-bg", "turret-bg", sf::Vector2f {(float)position_x, (float)position_y});

        /* Texts name are prefixed with an "a" because sfml window.draw put first rendered element in a queue on top of the others
         * in order to avoid the rectangle to overlap the texts these are forced to be on the top of the map as generator->registerDrawable
         * writes the element in an ordered-map
         */
        factory.instantiateText("a" + name + "-level",
                font,
                "",
                sf::Vector2f {(float)(position_x +5), (float)(position_y +5)},
                10,
                color,
                sf::Text::Style::Bold);
        factory.instantiateText("a" + name + "-power",
                font,
                "",
                sf::Vector2f {(float)(position_x +5), (float)(position_y +20)},
                10,
                color);
        factory.instantiateText("a" + name + "-fire-rate",
                font,
                "",
                sf::Vector2f {(float)(position_x +5), (float)(position_y +35)},
                10,
                color);
        factory.instantiateText("a" + name + "-upgrade-cost",
                font,
                "",
                sf::Vector2f {(float)(position_x +5), (float)(position_y +50)},
                10,
                color);

        int rad = turret->getRadius();
        radius_circle = factory.initCircleShape(name + "-turret-radius-overlay");
        radius_circle->setOrigin(sf::Vector2f {(float)(rad), (float)(rad)});
        radius_circle->setPosition(sf::Vector2f {(float)(x +20), (float)(y +20)});
        radius_circle->setRadius(rad);
        radius_circle->setFillColor(sf::Color(0x68, 0xac, 0x82, 0x55));
        radius_circle->setOutlineColor(sf::Color(0x6e, 0xa0, 0x70, 0x88));
        radius_circle->setOutlineThickness(2);
    }

    void callback() {
        generator->registerDrawable(name + "-turret-radius-overlay", factory.getCircleShape(name + "-turret-radius-overlay"));
        generator->registerDrawable("a" + name + "-level", factory.getText("a" + name + "-level"));
        generator->registerDrawable("a" + name + "-power", factory.getText("a" + name + "-power"));
        generator->registerDrawable("a" + name + "-fire-rate", factory.getText("a" + name + "-fire-rate"));
        generator->registerDrawable("a" + name + "-upgrade-cost", factory.getText("a" + name + "-upgrade-cost"));
        generator->registerDrawable("Z" + name + "-rect", factory.getSprite("turret-bg"));


        stringstream.str("");
        stringstream << "Level " << turret->getLevel();
        factory.getText("a" + name + "-level")->setString(stringstream.str());

        stringstream.str("");
        stringstream << "Power: " << turret->getPower();
        factory.getText("a" + name + "-power")->setString(stringstream.str());

        stringstream.str("");
        stringstream << "Fire rate: " << turret->getFireRate();
        factory.getText("a" + name + "-fire-rate")->setString(stringstream.str());

        stringstream.str("");
        stringstream << "Upgrade cost: " << turret->getUpgradeCost();
        factory.getText("a" + name + "-upgrade-cost")->setString(stringstream.str());
    }
};

#endif //TD_TOWERDEFENSE_SFML_PLACEDTURRETHOVER_H
