//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BUTTONICON_H
#define TD_TOWERDEFENSE_SFML_BUTTONICON_H

#include <SFML/Graphics.hpp>
#include "../Interface/Button.h"

class ButtonIcon : public Button {
private:
    sf::Sprite sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();         // apply the transform
        target.draw(sprite, states);                 // draw the shape array
    }
public:
    ButtonIcon() = default;

    ButtonIcon *setPosition(int x, int y);
    ButtonIcon *setTexture(sf::Texture *texture);
    ButtonIcon *setTextureRect(sf::IntRect rect);

    sf::Vector2f getSize();
    sf::Vector2f getPosition();
    sf::Sprite *getSprite();

    bool hasMouseHover(sf::Window *window);
};


#endif //TD_TOWERDEFENSE_SFML_BUTTONICON_H
