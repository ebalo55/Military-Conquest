//
// Created by ebalo on 20/03/20->
//

#include <iostream>
#include "ButtonRect.h"

ButtonRect::ButtonRect(int width, int height) {
    shape = new sf::RectangleShape(sf::Vector2f {(float)width, (float)height});
    label = new sf::Text();

    shape->setOutlineThickness(1);
    shape->setOutlineColor(colors[0]);
    shape->setFillColor(colors[1]);
    label->setFillColor(colors[2]);
}

ButtonRect *ButtonRect::setSize(int width, int height) {
    shape->setSize(sf::Vector2f {(float)width, (float)height});
    return this;
}

ButtonRect *ButtonRect::setPosition(int x, int y) {
    shape->setPosition(sf::Vector2f {(float)x, (float)y});
    return this;
}

ButtonRect *ButtonRect::setColor(sf::Color color, bool fill) {
    if(fill) {
        colors[1] = sf::Color(color);
        shape->setFillColor(colors[1]);
    }
    else {
        colors[0] = sf::Color(color);
        shape->setOutlineColor(colors[0]);
    }
    return this;
}

ButtonRect *ButtonRect::setLabel(sf::Font *font, const std::string& text, int size) {
    this->font = font;
    label->setFont(*this->font);
    label->setString(text);
    label->setCharacterSize(size);
    label->setPosition(sf::Vector2f {shape->getGlobalBounds().left + (shape->getLocalBounds().width - label->getLocalBounds().width) / 2,
                                    shape->getGlobalBounds().top + (shape->getLocalBounds().height /*- label->getLocalBounds().height*/ - size -2) / 2});
    return this;
}

ButtonRect *ButtonRect::setLabelColor(sf::Color color) {
    colors[2] = sf::Color(color);
    label->setFillColor(colors[2]);
    return this;
}

ButtonRect *ButtonRect::setLabelStyle(sf::Text::Style style) {
    label->setStyle(style);
    return this;
}

sf::Vector2f ButtonRect::getSize() {
    return shape->getSize();
}

sf::Vector2f ButtonRect::getPosition() {
    return sf::Vector2f {shape->getGlobalBounds().left, shape->getGlobalBounds().top};
}

sf::Color ButtonRect::getColor(bool fill) {
    return fill ? shape->getFillColor() : shape->getOutlineColor();
}

sf::Text *ButtonRect::getLabel() {
    return label;
}

sf::Color ButtonRect::getLabelColor() {
    return label->getFillColor();
}

sf::Uint32 ButtonRect::getLabelStyle() {
    return label->getStyle();
}

bool ButtonRect::hasMouseHover(sf::Window *window) {
    button_was_hover = !shape->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window));
    return !button_was_hover;
}

sf::RectangleShape *ButtonRect::getShape() {
    return shape;
}
