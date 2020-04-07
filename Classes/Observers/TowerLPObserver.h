//
// Created by ebalo on 23/03/20.
//

#ifndef TD_TOWERDEFENSE_TOWERLPOBSERVER_H
#define TD_TOWERDEFENSE_TOWERLPOBSERVER_H

#include "../Elements/Tower.h"
#include "../Interface/Observer.h"
#include "../RenderHandler.h"

class TowerLPObserver : public Observer {
private:
    Tower *tower;
    GAME_STATE *state;
public:
    TowerLPObserver(Tower *tower, GAME_STATE *state) :tower(tower), state(state) {
        tower->registerObserver(OBSERVERS_TYPE_ID::tower_lp, this);
    }

    void update() {
        if(tower->getHp() <= 0) {
            *state = GAME_STATE::game_over;
        }
    }
};

#endif //TD_TOWERDEFENSE_TOWERLPOBSERVER_H
