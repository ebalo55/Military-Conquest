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
    TurretGenerator *turret_generator;

    // If names.size = 8  =>  already_killed ~ 65500 killed enemies to get the last title
    double upgrade_factor = 2.25;
    unsigned long long already_killed = 0;

    std::vector<std::string> names;
    int name = -1;

public:
    KilledEnemies(unsigned long long first_step_required, TurretGenerator *turret_generator, std::vector<std::string> names, double upgrade_factor = 2.25)
        :Achievement(first_step_required), turret_generator(turret_generator), names(std::move(names)), upgrade_factor(upgrade_factor) {};

    void callback() override {
        /* As "goal" changes during the loop it will break the loop itself, if you ask yourself why a while loop the answer is
         * simple as the initial goal can be even 1 the loop ensure the execution of the upgrade and the goal update the right
         * number of times
         */
        while(already_killed >= goal) {
            // TODO: Show ribbon and upgrade all turret (+1)
            for(const sptr<Turret>& turret : turret_generator->getRegisteredTurretsAsReference()) {
                turret->upgrade();
            }
            goal *= upgrade_factor;

            if(name < (int)names.size()) {
                name++;
            }
            std::cout << names[name] << ". All turret upgraded, next step '" << names[name < names.size() -1 ? name +1 : name] << "' at " << goal << " killed enemies\n";
        }
    }

    void update(long long modifier) {
        already_killed += modifier;
    }
};

#endif //MILITARYCONQUEST_KILLEDENEMIES_H
