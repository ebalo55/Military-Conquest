//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_ENEMYGENERATORADAPTER_H
#define MILITARYCONQUEST_ENEMYGENERATORADAPTER_H

#include "../Elements/EnemyGenerator.h"

class EnemyGeneratorAdapter {
protected:
    sptr<EnemyGenerator> enemy_generator;
public:
    virtual void syncEnemies() {
        enemy_generator->syncEnemies();
    };
    virtual void tick(int time_lapse) {
        enemy_generator->tick(time_lapse);
    };
};

#endif //MILITARYCONQUEST_ENEMYGENERATORADAPTER_H
