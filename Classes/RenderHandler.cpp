//
// Created by ebalo on 20/03/20.
//

#include "RenderHandler.h"

RenderHandler::RenderHandler(sf::RenderWindow *window) :window(window) {
    maps = {new MapEasy(), new MapHard()};
}

RenderHandler::~RenderHandler() {
    for(int i = 0; i < maps.size(); i++) { delete maps[i]; }
}

void RenderHandler::handle() {
    window->clear();            // Clear the window
    window->draw(*(maps[0]));

    window->display();          // End frame and display content
}
