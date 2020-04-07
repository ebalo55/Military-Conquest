//
// Created by ebalo on 23/03/20.
//

#include "../Observers/EnemyLPObserver.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(GAME_STATE difficult, sptr<std::forward_list<sptr<Enemy>>> enemies, Tower *tower, std::vector<sptr<Map>> maps, bool game_type, sf::Texture *texture) {
    this->enemies = enemies;
    Map *map = game_type ? maps[0].get() : maps[1].get();
    initialized_instances = {
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 0, Enemy::Stats{75, 135, 0, 13, 900, 800},
                      ENEMY_TYPE::enemy1)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 1, Enemy::Stats{100, 115, 0, 15, 1000, 900},
                      ENEMY_TYPE::enemy2)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 2, Enemy::Stats{130, 100, 0, 20, 1250, 1150},
                      ENEMY_TYPE::enemy3)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 3, Enemy::Stats{150, 85, 0, 22, 1500, 1400},
                      ENEMY_TYPE::enemy4)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 4, Enemy::Stats{200, 70, 0, 30, 2000, 1900},
                      ENEMY_TYPE::enemy5)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 5, Enemy::Stats{400, 100, 0, 100, 4500, 3500},
                      ENEMY_TYPE::boss1)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 6, Enemy::Stats{2000, 50, 0, 300, 8000, 6500},
                      ENEMY_TYPE::boss2)),
            std::make_shared<Enemy>(new Enemy(map, game_type, texture, 7, Enemy::Stats{300, /*200*/400, 0, 175, 2000, 1000},
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
            sptr<Enemy> tmp = std::make_shared<Enemy>(new Enemy(initialized_instances[initialized_instances_map[line.first]].get()));
            new EnemyLPObserver(tmp, this, tower);
            enemies->push_front(tmp);
            generative_map[line.first]->time_since_round = 0;
            generative_map[line.first]->already_generated++;
        }
        else if(line.second->generation_delay > 0) { line.second->generation_delay -= time; }
    }
}

void EnemyGenerator::genFixedNumber(ENEMY_TYPE type, int amount, size_t delay) {
    generative_map[type] = std::make_shared<generativeConstructor>(generativeConstructor {0, 0, 0, delay, true, 0, amount});
    return this;
}

void EnemyGenerator::genForTime(ENEMY_TYPE type, size_t total_generation_time_millis, size_t delay) {
    generative_map[type] = std::make_shared<generativeConstructor>(generativeConstructor {0, 0, total_generation_time_millis, delay, true, 0, -1});
    return this;
}

void EnemyGenerator::tick(double time) {
    auto *to_remove = new std::map<ENEMY_TYPE, sptr<generativeConstructor>>::iterator[generative_map.size()];
    int i = 0;
    for(std::pair<ENEMY_TYPE, sptr<generativeConstructor>> elem : generative_map) {
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
    for(const sptr<Enemy>& enemy : initialized_instances) {
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

void EnemyGenerator::markEnemyAsToRemove(sptr<Enemy> enemy) {
    to_remove.push_back(enemy);
}

void EnemyGenerator::syncEnemies() {
    for(int i = 0; i < to_remove.size(); i++) {
        to_remove[i]->deleteObserver(OBSERVERS_TYPE_ID::enemy_lp);
        to_remove[i]->markAsDeleted();
        enemies->remove(to_remove[i]);
        to_remove[i].reset();
    }
    to_remove.clear();
}
