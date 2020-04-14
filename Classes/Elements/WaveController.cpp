//
// Created by ebalo on 13/04/20.
//

#include "WaveController.h"

WaveController::WaveController(GAME_STATE difficult, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies, const sptr<Tower>& tower, const std::vector<sptr<Map>>& maps, bool game_type)
    :Wave() {
    enemy_generator = std::make_shared<EnemyGenerator>(EnemyGenerator(difficult, enemies, tower, maps, game_type));
    this->enemies = enemies;

    boss_wave = difficult == GAME_STATE::game_difficulty_easy ? 10 : 5;

    waves_standard_template = {
            WaveData {ENEMY_TYPE::enemy1, false, 10},
            WaveData {ENEMY_TYPE::enemy1, false, 15},
            WaveData {ENEMY_TYPE::enemy1, false, 25},
            WaveData {ENEMY_TYPE::enemy1, true, 10},
            WaveData {ENEMY_TYPE::enemy1, true, 15},
            WaveData {ENEMY_TYPE::enemy1, true, 20},

            WaveData {ENEMY_TYPE::enemy2, false, 10},
            WaveData {ENEMY_TYPE::enemy2, false, 15},
            WaveData {ENEMY_TYPE::enemy2, false, 25},
            WaveData {ENEMY_TYPE::enemy2, true, 10},
            WaveData {ENEMY_TYPE::enemy2, true, 15},
            WaveData {ENEMY_TYPE::enemy2, true, 20},

            WaveData {ENEMY_TYPE::enemy3, false, 10},
            WaveData {ENEMY_TYPE::enemy3, false, 15},
            WaveData {ENEMY_TYPE::enemy3, false, 25},
            WaveData {ENEMY_TYPE::enemy3, true, 10},
            WaveData {ENEMY_TYPE::enemy3, true, 15},
            WaveData {ENEMY_TYPE::enemy3, true, 20},

            WaveData {ENEMY_TYPE::enemy4, false, 10},
            WaveData {ENEMY_TYPE::enemy4, false, 15},
            WaveData {ENEMY_TYPE::enemy4, false, 25},
            WaveData {ENEMY_TYPE::enemy4, true, 10},
            WaveData {ENEMY_TYPE::enemy4, true, 15},
            WaveData {ENEMY_TYPE::enemy4, true, 20},

            WaveData {ENEMY_TYPE::enemy5, false, 10},
            WaveData {ENEMY_TYPE::enemy5, false, 15},
            WaveData {ENEMY_TYPE::enemy5, false, 25},
            WaveData {ENEMY_TYPE::enemy5, true, 10},
            WaveData {ENEMY_TYPE::enemy5, true, 15},
            WaveData {ENEMY_TYPE::enemy5, true, 20},
    };

    waves_boss_template = {
            WaveData {ENEMY_TYPE::boss1, false, 3},
            WaveData {ENEMY_TYPE::boss1, false, 6},
            WaveData {ENEMY_TYPE::boss1, false, 10},
            WaveData {ENEMY_TYPE::boss1, true, 10},
            WaveData {ENEMY_TYPE::boss1, true, 15},
            WaveData {ENEMY_TYPE::boss1, true, 20},

            WaveData {ENEMY_TYPE::boss2, false, 3},
            WaveData {ENEMY_TYPE::boss2, false, 6},
            WaveData {ENEMY_TYPE::boss2, false, 10},
            WaveData {ENEMY_TYPE::boss2, true, 10},
            WaveData {ENEMY_TYPE::boss2, true, 15},
            WaveData {ENEMY_TYPE::boss2, true, 20},

            WaveData {ENEMY_TYPE::boss3, false, 3},
            WaveData {ENEMY_TYPE::boss3, false, 6},
            WaveData {ENEMY_TYPE::boss3, false, 10},
            WaveData {ENEMY_TYPE::boss3, true, 10},
            WaveData {ENEMY_TYPE::boss3, true, 15},
            WaveData {ENEMY_TYPE::boss3, true, 20},
    };
}

void WaveController::syncEnemies() {
    enemy_generator->syncEnemies();
}

void WaveController::tick(int time_lapse) {
    if(!count_down) {
        enemy_generator->tick(time_lapse);

        if(enemies->empty() && enemy_generator->getGenerativeMap()->empty()) {
            if(getWaveNumber() > 0 && getWaveNumber() % 2 == 0) {
                enemy_generator->upgrade();
            }
            wave_number++;
            count_down = true;
            clock.restart();

            // Generation function
            int packets = random.generate_uniform(1, 3);
            for(int i = 0; i < packets; i++) {
                WaveData data = waves_standard_template[random.generate_uniform(0, waves_standard_template.size() -1)];
                if(data.timed) {
                    enemy_generator->genForTime(data.type, data.number * 1000, i * random.generate_uniform(1000, 7500));
                }
                else {
                    enemy_generator->genFixedNumber(data.type, data.number, i * random.generate_uniform(1000, 7500));
                }
            }

            if(isBossWave()) {
                WaveData data = waves_boss_template[random.generate_uniform(0, waves_boss_template.size() -1)];
                if(data.timed) {
                    enemy_generator->genForTime(data.type, data.number * 1000, 0);
                }
                else {
                    enemy_generator->genFixedNumber(data.type, data.number, 0);
                }
            }
        }
    }

    if(count_down && time - (int)clock.getElapsedTime().asSeconds() <= 0) {
        count_down = false;
    }
}
