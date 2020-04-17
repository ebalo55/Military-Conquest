//
// Created by ebalo on 21/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_STARTBUTTONCLICK_H
#define TD_TOWERDEFENSE_SFML_STARTBUTTONCLICK_H

#include "../Interface/Event.h"
#include "../States/GameState.h"

class StartButtonClickEvent : public Event {
private:
    std::shared_ptr<GAME_STATE> state;
public:
    StartButtonClickEvent(std::shared_ptr<Button> btn, std::shared_ptr<GAME_STATE> state) : Event(btn), state(state) {}

    void callback() {
        *state = GAME_STATE::difficulty_screen;
    }
};

#endif //TD_TOWERDEFENSE_SFML_STARTBUTTONCLICK_H
