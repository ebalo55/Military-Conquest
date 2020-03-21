//
// Created by ebalo on 20/03/20.
//

#include "EventHandler.h"

EventHandler::EventHandler(sf::RenderWindow *window, GAME_STATE *state) :window(window), state(state) {

}

void EventHandler::handle() {
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) { window->close(); }
    }
}
