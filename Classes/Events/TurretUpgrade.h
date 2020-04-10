//
// Created by ebalo on 30/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_TURRETUPGRADE_H
#define TD_TOWERDEFENSE_SFML_TURRETUPGRADE_H

#include <utility>

#include "../Interface/Event.h"
#include "../Elements/Turret.h"
#include "../Elements/TurretGenerator.h"

class TurretUpgradeEvent : public Event {
private:
    std::shared_ptr<Turret> turret;
    std::shared_ptr<Tower> tower;
    Event *sender;
    TurretGenerator generator;
    std::string name;
public:
    TurretUpgradeEvent(std::shared_ptr<Button> btn, std::shared_ptr<Turret> turret, Event *sender, TurretGenerator& generator, std::string name)
        :Event(btn), turret(turret), tower(turret->getTower()), sender(sender), generator(generator), name(std::move(name)) {}

    void callback() {
        if(tower->pay(turret->getUpgradeCost())) {
            turret->upgrade();
            sender->setActiveState(false);

            // Recursively remove all the elements of the hover/click event
            for(std::string str : {"a" + name + "-level", "a" + name + "-power", "a" + name + "-fire-rate", "a" + name + "-upgrade-cost", name + "-rect", name + "-radius-circle", name + "-upgrade"}) {
                generator.deleteDrawable(str, true);
            }
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_TURRETUPGRADE_H
