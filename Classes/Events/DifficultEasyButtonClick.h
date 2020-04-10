//
// Created by ebalo on 22/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_DIFFICULTEASYBUTTONCLICK_H
#define TD_TOWERDEFENSE_SFML_DIFFICULTEASYBUTTONCLICK_H

#include <memory>
#include "../Interface/Event.h"
#include "../States/GameState.h"

class DifficultButtonClickEvent : public Event {
private:
    GAME_STATE *state, new_state;
public:
    DifficultButtonClickEvent(std::shared_ptr<Button> btn, GAME_STATE *state, GAME_STATE new_state) : Event(btn), state(state), new_state(new_state) {}

    void callback() {
        *state = new_state;
    }
};

#endif //TD_TOWERDEFENSE_SFML_DIFFICULTEASYBUTTONCLICK_H
