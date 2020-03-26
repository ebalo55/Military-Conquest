//
// Created by ebalo on 24/03/20.
//

#include "ButtonIcon.h"

ButtonIcon *ButtonIcon::setPosition(int x, int y) {
    sprite.setPosition(sf::Vector2f {(float)x, (float)y});
    return this;
}

ButtonIcon *ButtonIcon::setTexture(sf::Texture *texture) {
    sprite.setTexture(*texture);

    return this;
}

sf::Vector2f ButtonIcon::getSize() {
    return sf::Vector2f {sprite.getLocalBounds().width, sprite.getLocalBounds().height};
}

sf::Vector2f ButtonIcon::getPosition() {
    return sprite.getPosition();
}

sf::Sprite *ButtonIcon::getSprite() {
    return &sprite;
}

bool ButtonIcon::hasMouseHover(sf::Window *window) {
    button_was_hover = state_copy;
    state_copy = sprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window));
    return state_copy;
}

ButtonIcon *ButtonIcon::setTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
    return this;
}
