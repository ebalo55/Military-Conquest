//
// Created by ebalo on 26/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERABLEMAP_H
#define TD_TOWERDEFENSE_SFML_RENDERABLEMAP_H

#include <map>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Elements/ButtonRect.h"
#include "../Elements/ButtonIcon.h"

class RenderableMap {
protected:
    // Default renderable instances
    std::unordered_map<std::string, sf::Texture> textures_map;
    std::unordered_map<std::string, sf::Sprite> sprites_map;
    std::unordered_map<std::string, ButtonRect> rect_buttons_map;
    std::unordered_map<std::string, sf::Text> texts_map;
    std::unordered_map<std::string, ButtonIcon> icon_buttons_map;

    // Non default renderable instances
    std::map<std::string, sf::Drawable *> drawable_map;
    std::map<std::string, bool> drawable_lock_map;
public:
    enum Maps {
        textures,
        sprites,
        rect_buttons,
        texts,
        icons_button
    };

    sf::Sprite *initSprite(const std::string& name);
    sf::Sprite *getSprite(const std::string& name);
    const sf::Sprite *getSprite(const std::string& name) const;

    sf::Texture *initTexture(const std::string& name);
    sf::Texture *getTexture(const std::string& name);
    const sf::Texture *getTexture(const std::string& name) const;

    ButtonRect *initButtonRect(const std::string& name);
    ButtonRect *getButtonRect(const std::string& name);
    const ButtonRect *getButtonRect(const std::string& name) const;

    sf::Text *initText(const std::string& name);
    sf::Text * getText(const std::string& name);
    const sf::Text * getText(const std::string& name) const;

    ButtonIcon *initButtonIcon(const std::string& name);
    ButtonIcon *getButtonIcon(const std::string& name);
    const ButtonIcon *getButtonIcon(const std::string& name) const;

    // if_absent is deactivated, left for compatibility
    void registerDrawable(const std::string& name, sf::Drawable *drawable, bool if_absent = true, bool lock = false);
    bool deleteDrawable(const std::string& name, bool force = false);
    void unlockDrawable(const std::string& name);
    bool lockDrawable(const std::string& name);
    bool isDrawableLocked(const std::string& name);
    bool hasDrawable(const std::string& name);

    template <class map_type> static void clear(std::unordered_map<std::string, map_type> *map, const std::vector<std::string>& names) {
        for(const std::string& name : names) { map->erase(name); }
    }

    void clear(Maps map, const std::vector<std::string>& names);

    bool has(Maps map, const std::string& name) const;
};


#endif //TD_TOWERDEFENSE_SFML_RENDERABLEMAP_H
