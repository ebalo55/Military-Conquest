//
// Created by ebalo on 26/03/20.
//

#include "DrawableFactory.h"

void DrawableFactory::setEventHandler(EventHandler *event_handler) {
    this->event_handler = event_handler;
}

void DrawableFactory::setWindow(sf::RenderWindow *window) {
    this->window = window;
}

sf::Text *DrawableFactory::instantiateText(const std::string& name,
        sf::Font *font,
        const std::string& content,
        sf::Vector2f position,
        int size,
        sf::Color color,
        sf::Uint32 style
        ){
    sf::Text *text = initText(name);
    text->setFont(*font);
    text->setCharacterSize(size);
    text->setString(content);
    text->setStyle(style);
    text->setFillColor(color);
    text->setPosition(position);

    return text;
}

ButtonRect *DrawableFactory::instantiateButtonRect(const std::string &name,
        sf::Vector2i dimension,
        sf::Font *font,
        const std::string &label,
        int size,
        sf::Color btn_color,
        sf::Color label_color,
        sf::Vector2f position,
        bool activate,
        Event *mouse_out_event,
        Event *mouse_hover_event,
        Event *mouse_click_event
        ) {
    ButtonRect *button = initButtonRect(name);
    button->setSize(dimension.x, dimension.y);
    button->setColor(btn_color);
    button->setLabelColor(label_color);
    button->setPosition(position.x, position.y);
    button->setLabel(font, label, size);

    if(activate) {
        event_handler->registerButton(button);
        if(mouse_out_event != nullptr) { new MouseOutObserver(button, mouse_out_event, window); }
        if(mouse_hover_event != nullptr) { new MouseHoverObserver(button, mouse_hover_event, window); }
        if(mouse_click_event != nullptr) { new MouseClickObserver(button, mouse_click_event, window); }
    }

    return button;
}

ButtonIcon *DrawableFactory::instantiateButtonIcon(const std::string &name,
        sf::Texture *texture,
        sf::Vector2f position,
        sf::IntRect clip,
        bool activate,
        Event *mouse_out_event,
        Event *mouse_hover_event,
        Event *mouse_click_event
        ) {
    ButtonIcon *button = initButtonIcon(name);
    button->setTexture(texture);
    button->setPosition(position.x, position.y);
    if(clip.width > 0 && clip.height > 0) {
        button->setTextureRect(clip);
    }

    if(activate) {
        event_handler->registerButton(button);
        if(mouse_out_event != nullptr) { new MouseOutObserver(button, mouse_out_event, window); }
        if(mouse_hover_event != nullptr) { new MouseHoverObserver(button, mouse_hover_event, window); }
        if(mouse_click_event != nullptr) { new MouseClickObserver(button, mouse_click_event, window); }
    }

    return button;
}

ButtonIcon *DrawableFactory::instantiateButtonIcon(const std::string &name,
        const std::string &texture_name,
        sf::Vector2f position,
        sf::IntRect clip,
        bool activate,
        Event *mouse_out_event,
        Event *mouse_hover_event,
        Event *mouse_click_event
        ) {
    return instantiateButtonIcon(name, getTexture(texture_name), position, clip, activate, mouse_out_event, mouse_hover_event, mouse_click_event);
}

void DrawableFactory::linkEvent(Button *btn, Event *mouse_out_event, Event *mouse_hover_event, Event *mouse_click_event) {
    event_handler->registerButton(btn);
    if(mouse_out_event != nullptr) { new MouseOutObserver(btn, mouse_out_event, window); }
    if(mouse_hover_event != nullptr) { new MouseHoverObserver(btn, mouse_hover_event, window); }
    if(mouse_click_event != nullptr) { new MouseClickObserver(btn, mouse_click_event, window); }
}

sf::Texture *DrawableFactory::instantiateTexture(const std::string& name, const std::string& filename) {
    sf::Texture *texture = initTexture(name);
    texture->loadFromFile(filename);
    return texture;
}

sf::Sprite *DrawableFactory::instantiateSprite(const std::string &name, sf::Texture *texture, sf::Vector2f position, sf::IntRect clip) {
    sf::Sprite *sprite = initSprite(name);
    sprite->setTexture(*texture);
    sprite->setPosition(position);
    if(clip.width > 0 && clip.height > 0) {
        sprite->setTextureRect(clip);
    }
    return sprite;
}

sf::Sprite *DrawableFactory::instantiateSprite(const std::string &name, const sf::Texture *texture, sf::Vector2f position, sf::IntRect clip) {
    sf::Sprite *sprite = initSprite(name);
    sprite->setTexture(*texture);
    sprite->setPosition(position);
    if(clip.width > 0 && clip.height > 0) {
        sprite->setTextureRect(clip);
    }
    return sprite;
}

sf::Sprite *DrawableFactory::instantiateSprite(const std::string &name, const std::string &texture_name, sf::Vector2f position, sf::IntRect clip) {
    return instantiateSprite(name, getTexture(texture_name), position, clip);
}

void DrawableFactory::unlinkButton(Button *btn) {
    event_handler->deleteButton(btn);
}

void DrawableFactory::unlinkButton(const std::string& name, bool rect) {
    /* Only one of the results of the ternary operator is casted to the base class Button because both of the classes extends
     * Button but the two derived are incompatible.
     * In order to avoid compiler warnings/errors one is casted back to the base.
     * Note that the fact of using two different classes does not influence in any way the execution of the function as it has
     * as argument a Button pointer which both extend.
     */
    unlinkButton(rect ? (Button *)getButtonRect(name) : getButtonIcon(name));
}

void DrawableFactory::unlinkButton(const std::vector<std::string> &names, bool rect) {
    for(const std::string& name : names) { unlinkButton(name, rect); }
}

void DrawableFactory::linkButton(Button *btn) {
    event_handler->registerButton(btn);
}

void DrawableFactory::linkButton(const std::string &name, bool rect) {
    /* Only one of the results of the ternary operator is casted to the base class Button because both of the classes extends
     * Button but the two derived are incompatible.
     * In order to avoid compiler warnings/errors one is casted back to the base.
     * Note that the fact of using two different classes does not influence in any way the execution of the function as it has
     * as argument a Button pointer which both extend.
     */
    linkButton(rect ? (Button *)getButtonRect(name) : getButtonIcon(name));
}

void DrawableFactory::linkButton(const std::vector<std::string> &names, bool rect) {
    for(const std::string& name : names) { linkButton(name, rect); }
}
