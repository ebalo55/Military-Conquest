//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
#define TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class EventHandler {
private:
    sf::Event event;
    sf::RenderWindow *window;
public:
    EventHandler(sf::RenderWindow *window);
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
