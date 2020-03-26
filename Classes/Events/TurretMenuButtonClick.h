//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_TURRETMENUBUTTONCLICK_H
#define TD_TOWERDEFENSE_SFML_TURRETMENUBUTTONCLICK_H
#include "../Interface/Event.h"
#include "../States/GameState.h"
#include "../Elements/TurretGenerator.h"

class TurretMenuButtonClickEvent : public Event {
private:
    GAME_STATE *state;
    TurretGenerator *generator;
public:
    TurretMenuButtonClickEvent(Button *btn, TurretGenerator *generator) : Event(btn), generator(generator) {}

    void callback() {
        generator->switchMenuPage();
    }
};
#endif //TD_TOWERDEFENSE_SFML_TURRETMENUBUTTONCLICK_H
