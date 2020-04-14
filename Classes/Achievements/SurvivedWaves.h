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
public:
    SurvivedWaves(unsigned long long first_step_required, TurretGenerator *turret_generator, std::vector<std::string> names, double upgrade_factor = 5)
            :Achievement(first_step_required), names(std::move(names)), turret_generator(turret_generator) {};

    void callback() override {
        if(survived_waves >= goal) {
            // TODO: Show ribbon and upgrade one randomly chosen turret (+2)

            std::vector<sptr<Turret>> turrets = turret_generator->getRegisteredTurretsAsReference();
            sptr<Turret> turret = turrets[Random::generate(0, turrets.size() -1)];
            turret->upgrade();
            turret->upgrade();

            goal *= upgrade_factor;

            if(name < (int)names.size()) {
                name++;
            }
            std::cout << names[name] << ". One turret upgraded, next step '" << names[name < names.size() -1 ? name +1 : name] << "' at " << goal << " survived waves\n";
        }
    }

    void update(long long modificator = 0) {
        survived_waves = modificator;
    }
};

#endif //MILITARYCONQUEST_SURVIVEDWAVES_H
