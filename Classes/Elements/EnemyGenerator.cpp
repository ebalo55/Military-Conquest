//
// Created by ebalo on 23/03/20.
//

#include "../Observers/EnemyLPObserver.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(GAME_STATE difficult, sptr<std::map<unsigned long long, sptr<Enemy>>> enemies, sptr<Tower> tower, std::vector<sptr<Map>> maps, bool game_type) {
    this->enemies = enemies;
    this->difficult = difficult;
    sptr<Map> map = game_type ? maps[0] : maps[1];

    // TODO: the following line should be remove once the transition to the smart pointers is completed
    tileset = std::make_shared<sf::Texture>(sf::Texture());
    tileset->loadFromFile(AssetsMap::get("enemies-tile-set"));

    initialized_instances = {
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 0, Enemy::Stats{75, 135, 0, 13, 900, 800},
                      ENEMY_TYPE::enemy1)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 1, Enemy::Stats{100, 115, 0, 15, 1000, 900},
                      ENEMY_TYPE::enemy2)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 2, Enemy::Stats{130, 100, 0, 20, 1250, 1150},
                      ENEMY_TYPE::enemy3)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 3, Enemy::Stats{150, 85, 0, 22, 1500, 1400},
                      ENEMY_TYPE::enemy4)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 4, Enemy::Stats{200, 70, 0, 30, 2000, 1900},
                      ENEMY_TYPE::enemy5)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 5, Enemy::Stats{400, 100, 0, 100, 4500, 3500},
                      ENEMY_TYPE::boss1)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 6, Enemy::Stats{2000, 50, 0, 300, 8000, 6500},
                      ENEMY_TYPE::boss2)),
            std::make_shared<Enemy>(Enemy(map, game_type, tileset, 7, Enemy::Stats{300, 200, 0, 175, 2000, 1000},
                      ENEMY_TYPE::boss3, true, 8, 35)),
    };

    this->tower = tower;
    generateInstancesMap();
    enemies_generation_timer = {
            {ENEMY_TYPE::enemy1, initialized_instances[initialized_instances_map[ENEMY_TYPE::enemy1]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::enemy2, initialized_instances[initialized_instances_map[ENEMY_TYPE::enemy2]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::enemy3, initialized_instances[initialized_instances_map[ENEMY_TYPE::enemy3]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::enemy4, initialized_instances[initialized_instances_map[ENEMY_TYPE::enemy4]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::enemy5, initialized_instances[initialized_instances_map[ENEMY_TYPE::enemy5]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::boss1, initialized_instances[initialized_instances_map[ENEMY_TYPE::boss1]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::boss2, initialized_instances[initialized_instances_map[ENEMY_TYPE::boss2]]->getGenerationTime(difficult)},
            {ENEMY_TYPE::boss3, initialized_instances[initialized_instances_map[ENEMY_TYPE::boss3]]->getGenerationTime(difficult)}
    };
}

void EnemyGenerator::triggerGeneration(double time) {
    for(std::pair<ENEMY_TYPE, sptr<generativeConstructor>> line : generative_map) {
        if(line.second->started && line.second->generation_delay <= 0 && line.second->time_since_round >= enemies_generation_timer[line.first]) {
            sptr<Enemy> tmp = std::make_shared<Enemy>(Enemy(initialized_instances[initialized_instances_map[line.first]]));
            enemies->emplace(index++, tmp);
            // Register the enemy life observer
            new EnemyLPObserver(std::pair<unsigned long long, sptr<Enemy>>(index -1, enemies->at(index -1)), this, tower);
            // Prepend the enemy to the list


            // Reset the current instance of the generative map
            generative_map[line.first]->time_since_round = 0;
            generative_map[line.first]->already_generated++;
        }
        else if(line.second->generation_delay > 0) { line.second->generation_delay -= time; }
    }
}

void EnemyGenerator::genFixedNumber(ENEMY_TYPE type, int amount, size_t delay) {
    generative_map[type] = std::make_shared<generativeConstructor>(generativeConstructor {0, 0, 0, delay, true, 0, amount});
}

void EnemyGenerator::genForTime(ENEMY_TYPE type, size_t total_generation_time_millis, size_t delay) {
    generative_map[type] = std::make_shared<generativeConstructor>(generativeConstructor {0, 0, total_generation_time_millis, delay, true, 0, -1});
}

void EnemyGenerator::tick(double time) {
    // An array containing the old instances of the generative constructor that should be remove
    std::map<ENEMY_TYPE, sptr<generativeConstructor>>::iterator old_construct[generative_map.size()];
    int i = -1;

    for(std::pair<ENEMY_TYPE, sptr<generativeConstructor>> elem : generative_map) {
        if(elem.second->max_running_time != 0 && elem.second->total_elapsed_time >= elem.second->max_running_time) { elem.second->started = false; }
        if(elem.second->upper_bound != -1 && elem.second->already_generated >= elem.second->upper_bound) { elem.second->started = false; }

        if(elem.second->started && elem.second->generation_delay <= 0) {
            elem.second->total_elapsed_time += time;
            elem.second->time_since_round += time;
        }
        else if(!elem.second->started) {
            old_construct[++i] = generative_map.find(elem.first);
        }
    }

    for(; i >= 0; i--) {
        old_construct[i]->second.reset();
        generative_map.erase(old_construct[i]);
    }

    triggerGeneration(time);
}

void EnemyGenerator::generateInstancesMap() {
    int x = 0;
    for(const sptr<Enemy>& enemy : initialized_instances) {
        int hashcode = enemy->getType();
        if(hashcode == ENEMY_TYPE::enemy1) { initialized_instances_map[ENEMY_TYPE::enemy1] = x; }
        else if(hashcode == ENEMY_TYPE::enemy2) { initialized_instances_map[ENEMY_TYPE::enemy2] = x; }
        else if(hashcode == ENEMY_TYPE::enemy3) { initialized_instances_map[ENEMY_TYPE::enemy3] = x; }
        else if(hashcode == ENEMY_TYPE::enemy4) { initialized_instances_map[ENEMY_TYPE::enemy4] = x; }
        else if(hashcode == ENEMY_TYPE::enemy5) { initialized_instances_map[ENEMY_TYPE::enemy5] = x; }
        else if(hashcode == ENEMY_TYPE::boss1) { initialized_instances_map[ENEMY_TYPE::boss1] = x; }
        else if(hashcode == ENEMY_TYPE::boss2) { initialized_instances_map[ENEMY_TYPE::boss2] = x; }
        else if(hashcode == ENEMY_TYPE::boss3) { initialized_instances_map[ENEMY_TYPE::boss3] = x; }
        x++;
    }
}

void EnemyGenerator::markEnemyAsToRemove(unsigned long long enemy_id) {
    to_remove.push_back(enemy_id);
}

void EnemyGenerator::syncEnemies() {
    for(unsigned long long enemy_id : to_remove) {
        auto position = enemies->find(enemy_id);
        if(position != enemies->end()) {
            sptr<Enemy> enemy = enemies->at(enemy_id);
            enemy->deleteObserver(OBSERVERS_TYPE_ID::enemy_lp);
            enemy->markAsDeleted();
            enemy.reset();

            enemies->erase(position);
        }

    }
    to_remove.clear();
}

sptr<std::map<ENEMY_TYPE, sptr<generativeConstructor>>> EnemyGenerator::getGenerativeMap() {
    return std::make_shared<std::map<ENEMY_TYPE, sptr<generativeConstructor>>>(generative_map);
}

void EnemyGenerator::upgrade() {
    for(const sptr<Enemy>& enemy : initialized_instances) {
        enemy->upgrade();
    }
}

int EnemyGenerator::getGenerationTime(ENEMY_TYPE type) {
    return initialized_instances[initialized_instances_map.at(type)]->getGenerationTime(difficult);
}
