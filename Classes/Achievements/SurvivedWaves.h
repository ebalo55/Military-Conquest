//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_SURVIVEDWAVES_H
#define MILITARYCONQUEST_SURVIVEDWAVES_H

#include <utility>

#include "../Interface/Achievement.h"
#include "../Elements/TurretGenerator.h"

class SurvivedWaves : public Achievement {
private:
    TurretGenerator *turret_generator;

    // If names.size = 8  =>  already_killed ~ 256 killed enemies to get the last title
    double upgrade_factor = 1.5;
    unsigned long long survived_waves = 0;

    std::vector<std::string> names;
    int name = -1;
    std::stringstream stringstream;

public:
    SurvivedWaves(unsigned long long first_step_required, TurretGenerator *turret_generator, std::vector<std::string> names, double upgrade_factor = 1.5)
            :Achievement(first_step_required), names(std::move(names)), turret_generator(turret_generator), upgrade_factor(upgrade_factor) {};

    void callback() override {
        if(survived_waves >= goal) {
            std::vector<sptr<Turret>> turrets = turret_generator->getRegisteredTurretsAsReference();
            if(turrets.size() > 0) {
                sptr<Turret> turret = turrets[Random::generate(0, turrets.size() -1)];
                turret->upgrade();
                turret->upgrade();
            }

            goal *= upgrade_factor;

            if(name < (int)names.size()) {
                name++;
            }

            stringstream.str("");
            stringstream << "You have just been rewarded as " << names[name] << ", one of your\nturrets got +2 levels, next step '" << (names[name < names.size() -1 ? name +1 : name]) <<
                         "' at " << goal << " killed enemies";
            turret_generator->setUpReachedAchievement("Achievement reached", stringstream.str());
        }
    }

    void update(long long modificator = 0) {
        survived_waves = modificator;
    }
};

#endif //MILITARYCONQUEST_SURVIVEDWAVES_H
