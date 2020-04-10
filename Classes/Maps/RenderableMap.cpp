//
// Created by ebalo on 26/03/20.
//

#include <iostream>
#include "RenderableMap.h"

sptr<sf::Sprite> RenderableMap::initSprite(const std::string &name) {
    sprites_map[name] = std::make_shared<sf::Sprite>(sf::Sprite());
    return sprites_map[name];
}

sptr<sf::Sprite> RenderableMap::getSprite(const std::string &name) {
    return sprites_map[name];
}

sptr<sf::Sprite> RenderableMap::getSprite(const std::string &name) const {
    return sprites_map.at(name);
}

sptr<sf::Texture> RenderableMap::initTexture(const std::string &name) {
    textures_map[name] = std::make_shared<sf::Texture>(sf::Texture());
    return textures_map[name];
}

sptr<sf::Texture> RenderableMap::getTexture(const std::string &name) {
    return textures_map[name];
}

sptr<sf::Texture> RenderableMap::getTexture(const std::string &name) const {
    return textures_map.at(name);
}

sptr<ButtonRect> RenderableMap::initButtonRect(const std::string &name) {
    rect_buttons_map[name] = std::make_shared<ButtonRect>(ButtonRect());
    return rect_buttons_map[name];
}

sptr<ButtonRect> RenderableMap::getButtonRect(const std::string &name) {
    return rect_buttons_map[name];
}

sptr<ButtonRect> RenderableMap::getButtonRect(const std::string &name) const {
    return rect_buttons_map.at(name);
}

sptr<sf::Text> RenderableMap::initText(const std::string &name) {
    texts_map[name] = std::make_shared<sf::Text>(sf::Text());
    return texts_map[name];
}

sptr<sf::Text> RenderableMap::getText(const std::string &name) {
    return texts_map[name];
}

sptr<sf::Text> RenderableMap::getText(const std::string &name) const {
    return texts_map.at(name);
}

sptr<ButtonIcon> RenderableMap::initButtonIcon(const std::string &name) {
    icon_buttons_map[name] = std::make_shared<ButtonIcon>(ButtonIcon());
    return icon_buttons_map[name];
}

sptr<ButtonIcon> RenderableMap::getButtonIcon(const std::string &name) {
    return icon_buttons_map[name];
}

sptr<ButtonIcon> RenderableMap::getButtonIcon(const std::string &name) const {
    return icon_buttons_map.at(name);
}

void RenderableMap::registerDrawable(const std::string &name, sptr<sf::Drawable> drawable, bool if_absent, bool lock) {
    if(if_absent && drawable_map.find(name) == drawable_map.end()) {
        drawable_map[name] = drawable;
    }

    if(lock) { drawable_lock_map[name] = true; }
}

void RenderableMap::unlockDrawable(const std::string &name) {
    drawable_lock_map[name] = false;
}

bool RenderableMap::lockDrawable(const std::string &name) {
    if(drawable_map.find(name) != drawable_map.end()) {
        drawable_lock_map[name] = true;
        return true;
    }
    return false;
}

bool RenderableMap::isDrawableLocked(const std::string &name) {
    return drawable_map.find(name) != drawable_map.end() && drawable_lock_map.find(name) != drawable_lock_map.end() && drawable_lock_map[name];
}


bool RenderableMap::hasDrawable(const std::string &name) {
    return drawable_map.find(name) != drawable_map.end();
}

bool RenderableMap::deleteDrawable(const std::string &name, bool force) {
    auto position = drawable_map.find(name);
    auto lock_position = drawable_lock_map.find(name);
    bool is_locked = lock_position != drawable_lock_map.end();

    if(position != drawable_map.end()) {
        if((is_locked && drawable_lock_map[name] && force) || !(is_locked && drawable_lock_map[name])) {
            drawable_map.erase(position);
            if(is_locked) {
                drawable_lock_map.erase(lock_position);
            }
        }
        else { return false; }
    }
    return true;
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
