//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_KILLEDENEMIES_H
#define MILITARYCONQUEST_KILLEDENEMIES_H

#include <memory>
#include <vector>
#include "../Interface/Achievement.h"
#include "../Elements/Turret.h"

class KilledEnemies : public Achievement {
private:
    sptr<std::vector<sptr<Turret>>> turrets;

    double upgrade_factor = 5;
    unsigned long long already_killed;

public:
    KilledEnemies(unsigned long long first_step_required, double upgrade_factor = 5) :Achievement(first_step_required), {
        already_killed = 0;
    };

    void callback() override {
        if(already_killed >= goal) {
            // TODO: Show ribbon and upgrade all turret (+1)
            for(const sptr<Turret>& turret : *turrets) {
                turret->upgrade();
            }
            goal *= upgrade_factor;

            std::cout << "Achievement gained, turret updated, next achievement at " << goal << " killed enemies\n";
        }
    }

    template<class type> void update(type modifier) {};
    template<> void update<long long>(long long modifier) {
        already_killed += modifier;
    }
    template<> void update<sptr<std::vector<sptr<Turret>>>>(sptr<std::vector<sptr<Turret>>> modifier) {
        turrets = modifier;
    }
};

#endif //MILITARYCONQUEST_KILLEDENEMIES_H
