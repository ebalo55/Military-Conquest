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
    std::pair<unsigned long long, std::shared_ptr<Enemy>> enemy;
    EnemyGenerator *generator;
    std::shared_ptr<Tower> tower;

    bool already_executed = false;
public:
    EnemyLPObserver(std::pair<unsigned long long, std::shared_ptr<Enemy>> enemy, EnemyGenerator *generator, const std::shared_ptr<Tower>& tower) :enemy(enemy), generator(generator), tower(tower) {
        enemy.second->registerObserver(OBSERVERS_TYPE_ID::enemy_lp, this);
    }

    void update() {
        if(enemy.second->getHP() <= 0) {
            generator->markEnemyAsToRemove(enemy.first);
            int position = enemy.second->getPosition().x;
            if(enemy.second->getPosition().x + 20 < WINDOW_WIDTH) {
                tower->earn(already_executed ? 0 : enemy.second->getPower() / 2);
                already_executed = true;
            }
            else {
                tower->damage(enemy.second->getPower());
            }
        }
    }
};

#endif //TD_TOWERDEFENSE_ENEMYLPOBSERVER_H
