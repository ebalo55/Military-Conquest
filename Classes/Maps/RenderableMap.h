//
// Created by ebalo on 26/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERABLEMAP_H
#define TD_TOWERDEFENSE_SFML_RENDERABLEMAP_H

#include <memory>
#include <map>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../Elements/ButtonRect.h"
#include "../Elements/ButtonIcon.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class RenderableMap {
protected:
    // Default renderable instances
    std::unordered_map<std::string, sptr<sf::Texture>> textures_map;
    std::unordered_map<std::string, sptr<sf::Sprite>> sprites_map;
    std::unordered_map<std::string, sptr<ButtonRect>> rect_buttons_map;
    std::unordered_map<std::string, sptr<sf::Text>> texts_map;
    std::unordered_map<std::string, sptr<ButtonIcon>> icon_buttons_map;
    std::unordered_map<std::string, sptr<sf::CircleShape>> circle_shape_map;

    // Non default renderable instances
    std::map<std::string, sptr<sf::Drawable>> drawable_map;
    std::map<std::string, bool> drawable_lock_map;
public:
    enum Maps {
        textures,
        sprites,
        rect_buttons,
        texts,
        icons_button,
        circle
    };

    sptr<sf::Sprite> initSprite(const std::string& name);
    sptr<sf::Sprite> getSprite(const std::string& name);
    sptr<sf::Sprite> getSprite(const std::string& name) const;

    sptr<sf::Texture> initTexture(const std::string& name);
    sptr<sf::Texture> getTexture(const std::string& name);
    sptr<sf::Texture> getTexture(const std::string& name) const;

    sptr<ButtonRect> initButtonRect(const std::string& name);
    sptr<ButtonRect> getButtonRect(const std::string& name);
    sptr<ButtonRect> getButtonRect(const std::string& name) const;

    sptr<sf::Text> initText(const std::string& name);
    sptr<sf::Text> getText(const std::string& name);
    sptr<sf::Text> getText(const std::string& name) const;

    sptr<ButtonIcon> initButtonIcon(const std::string& name);
    sptr<ButtonIcon> getButtonIcon(const std::string& name);
    sptr<ButtonIcon> getButtonIcon(const std::string& name) const;

    sptr<sf::CircleShape> initCircleShape(const std::string& name);
    sptr<sf::CircleShape> getCircleShape(const std::string& name);
    sptr<sf::CircleShape> getCircleShape(const std::string& name) const;

    // if_absent is deactivated, left for compatibility
    void registerDrawable(const std::string& name, sptr<sf::Drawable> drawable, bool if_absent = true, bool lock = false);
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
