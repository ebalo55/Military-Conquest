//
// Created by ebalo on 23/03/20.
//

#include "../Observers/EnemyLPObserver.h"
#include "EnemyGenerator.h"
#include "../Parser/Config.h"

EnemyGenerator::EnemyGenerator(GAME_STATE difficult, sptr<std::map<unsigned long long, sptr<Enemy>>> enemies, sptr<Tower> tower, std::vector<sptr<Map>> maps, bool game_type) {
    this->enemies = enemies;
    this->difficult = difficult;
    sptr<Map> map = game_type ? maps[0] : maps[1];

    tileset = std::make_shared<sf::Texture>(sf::Texture());
    tileset->loadFromFile(AssetsMap::get("enemies-tile-set"));

    // Initialize instances using config.json
    std::shared_ptr<Config> config = Config::getInstance();
    for(EnemyStats stats : config->getAllEnemyStats()) {
        initialized_instances.push_back(std::make_shared<Enemy>(map, game_type, tileset, stats));
    }

    this->tower = tower;
    generateInstancesMap();

    // Fill the vector using the instances from the config
    for(std::pair<std::string, int> line : config->getLoopableEnemyType()) {
        enemies_generation_timer.emplace(line.second, initialized_instances[initialized_instances_map[line.second]]->getGenerationTime(difficult));
    }
}

void EnemyGenerator::triggerGeneration(double time) {
    for(std::pair<int, sptr<generativeConstructor>> line : generative_map) {
        if(line.second->started && line.second->generation_delay <= 0 && line.second->time_since_round >= enemies_generation_timer[line.first]) {
            sptr<Enemy> tmp = std::make_shared<Enemy>(Enemy(initialized_instances[initialized_instances_map[line.first]]));
            enemies->emplace(index++, tmp);
            // Register the enemy life observer
            new EnemyLPObserver(std::pair<unsigned long long, sptr<Enemy>>(index -1, enemies->at(index -1)), this, tower);

            // Reset the current instance of the generative map
            generative_map[line.first]->time_since_round = 0;
            generative_map[line.first]->already_generated++;
        }
        else if(line.second->generation_delay > 0) { line.second->generation_delay -= time; }
    }
}

void EnemyGenerator::genFixedNumber(int type, int amount, size_t delay) {
    generative_map[type] = std::make_shared<generativeConstructor>(generativeConstructor {0, 0, 0, delay, true, 0, amount});
}

void EnemyGenerator::genForTime(int type, size_t total_generation_time_millis, size_t delay) {
    generative_map[type] = std::make_shared<generativeConstructor>(generativeConstructor {0, 0, total_generation_time_millis, delay, true, 0, -1});
}

void EnemyGenerator::tick(double time) {
    // An array containing the old instances of the generative constructor that should be remove
    std::map<int, sptr<generativeConstructor>>::iterator old_construct[generative_map.size()];
    int i = -1;

    for(std::pair<int, sptr<generativeConstructor>> elem : generative_map) {
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
        int type = enemy->getType();

        for(std::pair<std::string, int> line : Config::getLoopableEnemyType()) {
            if(type == line.second) {
                initialized_instances_map[line.second] = x;
            }
        }
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

sptr<std::map<int, sptr<generativeConstructor>>> EnemyGenerator::getGenerativeMap() {
    return std::make_shared<std::map<int, sptr<generativeConstructor>>>(generative_map);
}

void EnemyGenerator::upgrade() {
    for(const sptr<Enemy>& enemy : initialized_instances) {
        enemy->upgrade();
    }
}

int EnemyGenerator::getGenerationTime(int type) {
    return initialized_instances[initialized_instances_map.at(type)]->getGenerationTime(difficult);
}
