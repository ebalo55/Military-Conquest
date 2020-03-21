//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#define TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#include <SFML/Graphics.hpp>
#include <vector>
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

    sf::Texture logo_texture;
    sf::Sprite logo;
    sf::Font comfortaa;
    ButtonRect start;

    void splashScreen();
public:
    RenderHandler(EventHandler *event_handler);
    ~RenderHandler();
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
