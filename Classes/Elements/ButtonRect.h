//
// Created by ebalo on 20/03/20.
//

#ifndef EXAM_BUTTON_H
#define EXAM_BUTTON_H

#include <SFML/Graphics.hpp>
#include "../Interface/Notifier.h"


class ButtonRect : public sf::Drawable, public sf::Transformable, public Notifier {
private:
    sf::RectangleShape *shape;
    sf::Text *label;
    sf::Font *font;
    sf::Color colors[3] = {
            sf::Color(0, 0, 0),                       // Button outline
            sf::Color(0, 0, 0, 0),              // Button fill
            sf::Color(0, 0, 0)                        // Label fill
    };

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();         // apply the transform
        target.draw(*shape, states);                 // draw the shape array
        target.draw(*label, states);
    }
public:
    ButtonRect(int width = 1, int height = 1);

    ButtonRect *setSize(int width, int height);
    ButtonRect *setPosition(int x, int y);
    ButtonRect *setColor(sf::Color color, bool fill = false);
    ButtonRect *setLabel(sf::Font *font, const std::string& text, int size = 12);
    ButtonRect *setLabelColor(sf::Color color);
    ButtonRect *setLabelStyle(sf::Text::Style style);

    sf::Vector2f getSize();
    sf::Vector2f getPosition();
    sf::Color getColor(bool fill = false);
    sf::Text *getLabel();
    sf::Color getLabelColor();
    sf::Uint32 getLabelStyle();

    bool hasMouseHover(sf::Window *window);
};


#endif //EXAM_BUTTON_H
