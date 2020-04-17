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
    TurretGenerator *generator;
    bool forward;
public:
    TurretMenuButtonClickEvent(std::shared_ptr<Button> btn, TurretGenerator *generator, bool forward = true) : Event(
            btn), generator(generator), forward(forward) {}

    void callback() {
        generator->switchMenuPage(forward);
    }
};
#endif //TD_TOWERDEFENSE_SFML_TURRETMENUBUTTONCLICK_H
