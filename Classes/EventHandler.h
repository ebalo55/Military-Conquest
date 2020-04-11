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

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class EventHandler : public Notifier {
private:
    enum QueueOpCode {
        add,
        remove,
        hide
    };

    sf::Event event;
    sptr<sf::RenderWindow> window;

    bool turret_insertion_loop = false;
    sptr<GAME_STATE> state;

    std::list<sptr<Button>> buttons;
    std::vector<std::pair<QueueOpCode, sptr<Button>>> queue;

    void notifyButtons(OBSERVERS_TYPE_ID ev_code);
    void queueWorker();
public:
    EventHandler(sptr<sf::RenderWindow> window, sptr<GAME_STATE> state);
    void handle();

    sptr<GAME_STATE> getGameState();
    sptr<sf::RenderWindow> getRenderWindow();

    void registerButton(const sptr<Button>& btn);
    void deleteButton(sptr<Button >btn);
    void hideButton(const sptr<Button>& btn);

    void addToRemoveList(const sptr<Button>& btn);
    void addToHideList(const sptr<Button>& btn);
    void addToList(const sptr<Button>& btn);
};


#endif //TD_TOWERDEFENSE_SFML_EVENTHANDLER_H
