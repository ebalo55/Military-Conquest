//
// Created by ebalo on 13/04/20.
//

#include "WaveController.h"
#include "../Achievements/KilledEnemies.h"
#include "../Achievements/SurvivedWaves.h"

WaveController::WaveController(GAME_STATE difficult, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies, const sptr<Tower>& tower, const std::vector<sptr<Map>>& maps, bool game_type)
    :Wave() {
    enemy_generator = std::make_shared<EnemyGenerator>(EnemyGenerator(difficult, enemies, tower, maps, game_type));
    this->enemies = enemies;

    boss_wave = difficult == GAME_STATE::game_difficulty_easy ? 10 : 5;

    // Load all the wave template from the configuration file
    sptr<Config> config = Config::getInstance();
    buildWaveTemplate(waves_standard_template, config->getAllEnemiesType(), config->getEnemyWaveTemplate());
    buildWaveTemplate(waves_boss_template, config->getAllBossesType(), config->getBossWaveTemplate());
}

void WaveController::tick(int time_lapse) {
    if(!count_down) {
        enemy_generator->tick(time_lapse);

        if(enemies->empty() && enemy_generator->getGenerativeMap()->empty()) {
            wave_number++;
            notify(OBSERVERS_TYPE_ID::killed_enemies, AchievementObserver::Method::both, total_enemies);
            notify(OBSERVERS_TYPE_ID::survived_waves, AchievementObserver::Method::both, wave_number -1);

            total_enemies = 0;
            if(getWaveNumber() > 0 && getWaveNumber() % 2 == 0) {
                enemy_generator->upgrade();
            }
            count_down = true;
            clock.restart();

            // Generation function
            int packets = random.generate_uniform(1, 3);
            for(int i = 0; i < packets; i++) {
                triggerGeneration(waves_standard_template, i);
            }

            if(isBossWave()) {
                triggerGeneration(waves_boss_template, 0);
            }
        }
    }

    if(count_down && time - (int)clock.getElapsedTime().asSeconds() <= 0) {
        count_down = false;
    }
}

void WaveController::initObservers(TurretGenerator *turret_generator) {
    /* Generate the achievements using the data from the configuration.
     * As the observer is implemented using a map multiple instances with the same id will overwrite each other and only
     * the last one will be used.
     */
    for (const AchievementInfo &info : Config::getInstance()->getAchievements()) {
        if (info.type == OBSERVERS_TYPE_ID::killed_enemies) {
            registerObserver(info.type, new AchievementObserver(std::unique_ptr<Achievement>(
                    new KilledEnemies(info.first_goal, turret_generator, info.names, info.upgrade_factor))));
        } else {
            registerObserver(info.type, new AchievementObserver(std::unique_ptr<Achievement>(
                    new SurvivedWaves(info.first_goal, turret_generator, info.names, info.upgrade_factor))));
        }
    }
}

void WaveController::triggerGeneration(const std::vector<WaveData>& wave_data, int index) {
    WaveData data = wave_data[random.generate_uniform(0, wave_data.size() - 1)];
    if (data.timed) {
        total_enemies += data.number * 1000 / enemy_generator->getGenerationTime(data.type);
        enemy_generator->genForTime(data.type, data.number * 1000, index * random.generate_uniform(1000, 7500));
    } else {
        total_enemies += data.number;
        enemy_generator->genFixedNumber(data.type, data.number, index * random.generate_uniform(1000, 7500));
    }
}

void WaveController::buildWaveTemplate(std::vector<WaveData> &target, const std::vector<int> &types,
                                       const std::vector<std::pair<bool, int>> &variation) {
    for (int type : types) {
        for (std::pair<bool, int> line : variation) {
            target.emplace_back(type, line.first, line.second);
        }
    }
}
