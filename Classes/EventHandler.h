//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
#define TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "States/GameState.h"
#include "Interface/Notifier.h"
#include "Interface/Button.h"
#include "Interface/FakeButton.h"

class EventHandler : public Notifier {
private:
    sf::Event event;
    sf::RenderWindow *window;

    bool turret_insertion_loop = false;
    GAME_STATE *state;

    std::list<Button *> buttons;
    std::vector<Button *> to_remove;
    std::vector<Button *> to_add;

    void notifyButtons(OBSERVERS_TYPE_ID ev_code);
public:
    EventHandler(sf::RenderWindow *window, GAME_STATE *state);
    void handle();

    GAME_STATE *getGameState();
    sf::RenderWindow *getRenderWindow();

    void registerButton(Button *btn);
    void deleteButton(Button *btn);

    void addToRemoveList(Button *btn);
    void addToList(Button *btn);
};


#endif //TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
