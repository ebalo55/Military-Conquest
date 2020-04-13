//
// Created by ebalo on 23/03/20.
//

#ifndef TD_TOWERDEFENSE_ENEMYLPOBSERVER_H
#define TD_TOWERDEFENSE_ENEMYLPOBSERVER_H

#include <memory>
#include "../Elements/Enemy.h"
#include "../States/ObserversTypeId.h"
#include "../Elements/EnemyGenerator.h"

class EnemyLPObserver : public Observer {
private:
    std::shared_ptr<Enemy> enemy;
    EnemyGenerator *generator;
    std::shared_ptr<Tower> tower;
public:
    EnemyLPObserver(std::shared_ptr<Enemy> enemy, EnemyGenerator *generator, const std::shared_ptr<Tower>& tower) :enemy(enemy), generator(generator), tower(tower) {
        enemy->registerObserver(OBSERVERS_TYPE_ID::enemy_lp, this);
    }

    void update() {
        if(enemy->getHP() <= 0) {
            generator->markEnemyAsToRemove(enemy);
            int position = enemy->getPosition().x;
            if(enemy->getPosition().x + 20 < WINDOW_WIDTH) {
                tower->earn(enemy->getPower() / 2);
            }
            else {
                tower->damage(enemy->getPower());
            }
        }
    }
};

#endif //TD_TOWERDEFENSE_ENEMYLPOBSERVER_H
