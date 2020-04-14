//
// Created by ebalo on 13/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_WAVECONTROLLER_H
#define TD_TOWERDEFENSE_SFML_WAVECONTROLLER_H

#include <memory>
#include "EnemyGenerator.h"
#include "../Interface/Wave.h"
#include "../Interface/Random.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class WaveController : public Wave {
private:
    sptr<EnemyGenerator> enemy_generator;
    sptr<std::map<unsigned long long, sptr<Enemy>>> enemies;

    struct WaveData {
        ENEMY_TYPE type;
        bool timed;
        int number;
    };

    std::vector<WaveData> waves_standard_template;
    std::vector<WaveData> waves_boss_template;
    Random random;

public:
    WaveController(GAME_STATE difficult, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies, const sptr<Tower>& tower, const std::vector<sptr<Map>>& maps, bool game_type);

    // TODO: Move the following function into an adapter and extend it
    void syncEnemies();
    void tick(int time_lapse);
};


#endif //TD_TOWERDEFENSE_SFML_WAVECONTROLLER_H
