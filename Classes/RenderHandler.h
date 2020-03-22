//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#define TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "Maps/Map.h"
#include "Maps/MapEasy.h"
#include "Maps/MapHard.h"
#include "States/GameState.h"
#include "Elements/ButtonRect.h"
#include "EventHandler.h"

class RenderHandler {
private:
    sf::RenderWindow *window;
    EventHandler *event_handler;

    std::vector<Map *> maps;
    GAME_STATE *state;

    std::unordered_map<std::string, sf::Texture> textures_map;
    std::unordered_map<std::string, sf::Sprite> sprites_map;
    std::unordered_map<std::string, ButtonRect> rect_buttons_map;
    sf::Texture logo_texture,
        rounded_box_texture;
    sf::Sprite logo,
        rounded_box;
    sf::Font comfortaa;
    ButtonRect start;

    sf::Sprite *initSprite(std::string name);
    sf::Sprite *getSprite(std::string name);
    sf::Texture *initTexture(std::string name);
    sf::Texture *getTexture(std::string name);

    void splashScreen();
    void difficultScreen();
public:
    RenderHandler(EventHandler *event_handler);
    ~RenderHandler();
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
