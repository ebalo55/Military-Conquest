//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#define TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Maps/Map.h"
#include "Maps/MapEasy.h"
#include "Maps/MapHard.h"

class RenderHandler {
private:
    sf::RenderWindow *window;

    std::vector<Map *> maps;
public:
    RenderHandler(sf::RenderWindow *window);
    ~RenderHandler();
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
