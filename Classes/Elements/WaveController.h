//
// Created by ebalo on 13/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_WAVECONTROLLER_H
#define TD_TOWERDEFENSE_SFML_WAVECONTROLLER_H

#include <memory>
#include "EnemyGenerator.h"
#include "../Interface/Wave.h"
#include "../Interface/Random.h"
#include "../Interface/AchievementNotifier.h"
#include "../Adapters/EnemyGeneratorAdapter.h"
#include "TurretGenerator.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class WaveController : public EnemyGeneratorAdapter, public Wave, public AchievementNotifier {
private:
    sptr<std::map<unsigned long long, sptr<Enemy>>> enemies;

    struct WaveData {
        ENEMY_TYPE type;
        bool timed;
        int number;
    };

    std::vector<WaveData> waves_standard_template;
    std::vector<WaveData> waves_boss_template;
    Random random;

    int total_enemies = 0;

    void triggerGeneration(const std::vector<WaveData>& wave_data, int index = 0);
public:
    WaveController(GAME_STATE difficult, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies, const sptr<Tower>& tower, const std::vector<sptr<Map>>& maps, bool game_type);

    void initObservers(TurretGenerator *turret_generator);
    void tick(int time_lapse) override;
};


#endif //TD_TOWERDEFENSE_SFML_WAVECONTROLLER_H
