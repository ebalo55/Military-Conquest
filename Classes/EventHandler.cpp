//
// Created by ebalo on 20/03/20.
//

#include "EventHandler.h"

EventHandler::EventHandler(sf::RenderWindow *window) :window(window) {

}

void EventHandler::handle() {
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) { window->close(); }
    }
}
