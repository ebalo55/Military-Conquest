//
// Created by ebalo on 23/03/20.
//

#include "../Observers/EnemyLPObserver.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(GAME_STATE difficult, std::forward_list<Enemy *> *enemies, Tower *tower, std::vector<Enemy *> init_instances) {
    this->enemies = enemies;
    this->initialized_instances = std::move(init_instances);
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
    for(std::pair<ENEMY_TYPE, generativeConstructor *> line : generative_map) {
        if(line.second->started && line.second->generation_delay <= 0 && line.second->time_since_round >= enemies_generation_timer[line.first]) {
            auto *tmp = new Enemy(initialized_instances[initialized_instances_map[line.first]]);
            new EnemyLPObserver(tmp, this, tower);
            enemies->push_front(tmp);
            generative_map[line.first]->time_since_round = 0;
            generative_map[line.first]->already_generated++;
        }
        else if(line.second->generation_delay > 0) { line.second->generation_delay -= time; }
    }
}

EnemyGenerator *EnemyGenerator::genFixedNumber(ENEMY_TYPE type, int amount, size_t delay) {
    generative_map[type] = new generativeConstructor {0, 0, 0, delay, true, 0, amount};
    return this;
}

EnemyGenerator *EnemyGenerator::genForTime(ENEMY_TYPE type, size_t total_generation_time_millis, size_t delay) {
    generative_map[type] = new generativeConstructor {0, 0, total_generation_time_millis, delay, true, 0, -1};
    return this;
}

EnemyGenerator *EnemyGenerator::tick(double time) {
    auto *to_remove = new std::map<ENEMY_TYPE, generativeConstructor*>::iterator[generative_map.size()];
    int i = 0;
    for(std::pair<ENEMY_TYPE, generativeConstructor *> elem : generative_map) {
        if(elem.second->max_running_time != 0 && elem.second->total_elapsed_time >= elem.second->max_running_time) { elem.second->started = false; }
        if(elem.second->upper_bound != -1 && elem.second->already_generated >= elem.second->upper_bound) { elem.second->started = false; }

        if(elem.second->started && elem.second->generation_delay <= 0) {
            elem.second->total_elapsed_time += time;
            elem.second->time_since_round += time;
        }
        else if(!elem.second->started) {
            to_remove[i++] = generative_map.find(elem.first);
        }
    }

    for(size_t j = 0; j < i; j++) {
        generative_map.erase(to_remove[j]);
    }
    delete[] to_remove;

    triggerGeneration(time);
    return this;
}

void EnemyGenerator::generateInstancesMap() {
    int x = 0;
    for(Enemy * enemy : initialized_instances) {
        int hashcode = enemy->getHashCode();
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

void EnemyGenerator::markEnemyAsToRemove(Enemy *enemy) {
    to_remove.push_back(enemy);
}

void EnemyGenerator::syncEnemies() {
    for(Enemy *enemy : to_remove) {
        enemies->remove(enemy);
        delete enemy;
    }
    to_remove.clear();
}
