//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_TURRETADAPTER_H
#define MILITARYCONQUEST_TURRETADAPTER_H

#include <memory>
#include <map>
#include "../Elements/Enemy.h"
#include "../Elements/Turret.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class TurretAdapter {
protected:
    std::vector<sptr<Turret>> turrets;
public:
    void moveBullets(int elapsed_time, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies) {
        for(const sptr<Turret>& turret : turrets) {
            turret->moveBullets(elapsed_time, enemies);
        }
    }
    void triggerBulletCollisionDetection(const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies) {
        /* The following code is simply an hack to trigger the collision detection and bullet pointer reset on all the
         * bullets fired by all the turrets, the time set to 0 let the bullets remain in the same position while the remaining
         * code is executed as desired.
         */
        for(const sptr<Turret>& turret : turrets) {
            turret->moveBullets(0, enemies);
        }
    }
    void notifyMovementToTurrets(sptr<Enemy>& enemy, int elapsed_time) {
        for(const sptr<Turret>& turret : turrets) {
            turret->notify(enemy, elapsed_time);
        }
    }
};

#endif //MILITARYCONQUEST_TURRETADAPTER_H
