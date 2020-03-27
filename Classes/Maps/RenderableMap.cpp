//
// Created by ebalo on 26/03/20.
//

#include "RenderableMap.h"

sf::Sprite *RenderableMap::initSprite(const std::string &name) {
    sprites_map[name] = sf::Sprite();
    return &sprites_map[name];
}

sf::Sprite *RenderableMap::getSprite(const std::string &name) {
    return &sprites_map[name];
}

const sf::Sprite *RenderableMap::getSprite(const std::string &name) const {
    return &sprites_map.at(name);
}

sf::Texture *RenderableMap::initTexture(const std::string &name) {
    textures_map[name] = sf::Texture();
    return &textures_map[name];
}

sf::Texture *RenderableMap::getTexture(const std::string &name) {
    return &textures_map[name];
}

const sf::Texture *RenderableMap::getTexture(const std::string &name) const {
    return &textures_map.at(name);
}

ButtonRect *RenderableMap::initButtonRect(const std::string &name) {
    rect_buttons_map[name] = ButtonRect();
    return &rect_buttons_map[name];
}

ButtonRect *RenderableMap::getButtonRect(const std::string &name) {
    return &rect_buttons_map[name];
}

const ButtonRect *RenderableMap::getButtonRect(const std::string &name) const {
    return &rect_buttons_map.at(name);
}

sf::Text *RenderableMap::initText(const std::string &name) {
    texts_map[name] = sf::Text();
    return &texts_map[name];
}

sf::Text *RenderableMap::getText(const std::string &name) {
    return &texts_map[name];
}

const sf::Text *RenderableMap::getText(const std::string &name) const {
    return &texts_map.at(name);
}

ButtonIcon *RenderableMap::initButtonIcon(const std::string &name) {
    icon_buttons_map[name] = ButtonIcon();
    return &icon_buttons_map[name];
}

ButtonIcon *RenderableMap::getButtonIcon(const std::string &name) {
    return &icon_buttons_map[name];
}

const ButtonIcon *RenderableMap::getButtonIcon(const std::string &name) const {
    return &icon_buttons_map.at(name);
}

void RenderableMap::registerDrawable(const std::string &name, sf::Drawable *drawable, bool if_absent) {
    if(if_absent && drawable_map.find(name) == drawable_map.end()) {
        drawable_map[name] = drawable;
    }
    else if(!if_absent) { drawable_map[name] = drawable; }
}

void RenderableMap::deleteDrawable(const std::string &name) {
    auto position = drawable_map.find(name);
    if(position != drawable_map.end()) {
        drawable_map.erase(position);
    }
}

void RenderableMap::clear(RenderableMap::Maps map, const std::vector<std::string> &names) {
    switch(map) {
        case textures:
            RenderableMap::clear(&textures_map, names);
            break;
        case sprites:
            RenderableMap::clear(&sprites_map, names);
            break;
        case rect_buttons:
            RenderableMap::clear(&rect_buttons_map, names);
            break;
        case texts:
            RenderableMap::clear(&texts_map, names);
            break;
        case icons_button:
            RenderableMap::clear(&icon_buttons_map, names);
            break;
    }
}

bool RenderableMap::has(RenderableMap::Maps map, const std::string &name) const {
    switch(map) {
        case textures:
            return textures_map.find(name) != textures_map.end();
        case sprites:
            return sprites_map.find(name) != sprites_map.end();
        case rect_buttons:
            return rect_buttons_map.find(name) != rect_buttons_map.end();
        case texts:
            return texts_map.find(name) != texts_map.end();
        case icons_button:
            return icon_buttons_map.find(name) != icon_buttons_map.end();
    }
}
