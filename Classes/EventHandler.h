//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
#define TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "States/GameState.h"
#include "Interface/Notifier.h"
#include "Interface/Button.h"
#include "Interface/FakeButton.h"

class EventHandler : public Notifier {
private:
    enum QueueOpCode {
        add,
        remove,
        hide
    };

    sf::Event event;
    std::shared_ptr<sf::RenderWindow> window;

    bool turret_insertion_loop = false;
    std::shared_ptr<GAME_STATE> state;

    std::list<Button *> buttons;
    std::vector<std::pair<QueueOpCode, Button *>> queue;

    void notifyButtons(OBSERVERS_TYPE_ID ev_code);
    void queueWorker();
public:
    EventHandler(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<GAME_STATE> state);
    void handle();

    std::shared_ptr<GAME_STATE> getGameState();
    std::shared_ptr<sf::RenderWindow> getRenderWindow();

    void registerButton(Button *btn);
    void deleteButton(Button *btn);
    void hideButton(Button *btn);

    void addToRemoveList(Button *btn);
    void addToHideList(Button *btn);
    void addToList(Button *btn);
};


#endif //TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
