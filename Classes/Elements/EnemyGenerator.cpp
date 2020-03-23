//
// Created by ebalo on 13/03/20.
//

#include "EnemyGenerator.h"
/*#include "../Observers/EnemyLPObserver.h"

#include <utility>

EnemyGenerator::EnemyGenerator(GAME_OPT difficult, std::forward_list<Enemy *> *enemies, std::vector<Enemy *> init_instances) {
    this->enemies = enemies;
    this->initialized_instances = std::move(init_instances);
    generateInstancesMap();
    enemies_generation_timer = {
            {enemy1, initialized_instances[initialized_instances_map[enemy1]]->getGenerationTime(difficult) *1000},
            {enemy2, initialized_instances[initialized_instances_map[enemy2]]->getGenerationTime(difficult) *1000},
            {enemy3, initialized_instances[initialized_instances_map[enemy3]]->getGenerationTime(difficult) *1000},
            {enemy4, initialized_instances[initialized_instances_map[enemy4]]->getGenerationTime(difficult) *1000},
            {enemy5, initialized_instances[initialized_instances_map[enemy5]]->getGenerationTime(difficult) *1000},
            {boss1, initialized_instances[initialized_instances_map[boss1]]->getGenerationTime(difficult) *1000},
            {boss2, initialized_instances[initialized_instances_map[boss2]]->getGenerationTime(difficult) *1000},
            {boss3, initialized_instances[initialized_instances_map[boss3]]->getGenerationTime(difficult) *1000}
    };
}

void EnemyGenerator::triggerGeneration(double time) {
    for(std::pair<unsigned long long, generativeConstructor *> line : generative_map) {
        if(line.second->started && line.second->generation_delay <= 0 && line.second->time_since_round >= enemies_generation_timer[line.first]) {
            auto *tmp = new Enemy(initialized_instances[initialized_instances_map[line.first]]);
            new EnemyLPObserver(tmp, enemies);
            enemies->push_front(tmp);
            generative_map[line.first]->time_since_round = 0;
            generative_map[line.first]->already_generated++;
        }
        else if(line.second->generation_delay > 0) { line.second->generation_delay -= time; }
    }
}

EnemyGenerator *EnemyGenerator::genFixedNumber(ENEMY_TYPE type, int amount, size_t delay) {
    generative_map[type == ::enemy1 ? enemy1 :
        type == ::enemy2 ? enemy2 :
        type == ::enemy3 ? enemy3 :
        type == ::enemy4 ? enemy4 :
        type == ::enemy5 ? enemy5 :
        type == ::boss1 ? boss1 :
        type == ::boss2 ? boss2 : boss3] = new generativeConstructor {0, 0, 0, delay, true, 0, amount};
    return this;
}

EnemyGenerator *EnemyGenerator::genForTime(ENEMY_TYPE type, size_t total_generation_time_millis, size_t delay) {
    generative_map[type == ::enemy1 ? enemy1 :
        type == ::enemy2 ? enemy2 :
        type == ::enemy3 ? enemy3 :
        type == ::enemy4 ? enemy4 :
        type == ::enemy5 ? enemy5 :
        type == ::boss1 ? boss1 :
        type == ::boss2 ? boss2 : boss3] = new generativeConstructor {0, 0, total_generation_time_millis, delay, true, 0, -1};
    return this;
}

EnemyGenerator *EnemyGenerator::timeTick(double time) {
    std::map<int, generativeConstructor*>::iterator *to_remove = new std::map<int, generativeConstructor*>::iterator[generative_map.size()];
    int i = 0;
    for(std::pair<int, generativeConstructor *> elem : generative_map) {
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
    enemy1 = 0;
    enemy2 = 1;
    enemy3 = 2;
    enemy4 = 3;
    enemy5 = 4;
    boss1 = 5;
    boss2 = 6;
    boss3 = 7;

    int x = 0;
    for(Enemy * enemy : initialized_instances) {
        int hashcode = enemy->getHashCode();
        if(hashcode == enemy1) { initialized_instances_map[enemy1] = x; }
        else if(hashcode == enemy2) { initialized_instances_map[enemy2] = x; }
        else if(hashcode == enemy3) { initialized_instances_map[enemy3] = x; }
        else if(hashcode == enemy4) { initialized_instances_map[enemy4] = x; }
        else if(hashcode == enemy5) { initialized_instances_map[enemy5] = x; }
        else if(hashcode == boss1) { initialized_instances_map[boss1] = x; }
        else if(hashcode == boss2) { initialized_instances_map[boss2] = x; }
        else if(hashcode == boss3) { initialized_instances_map[boss3] = x; }
        x++;
    }
}
*/