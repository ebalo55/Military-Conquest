//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_BATTLETEST_H
#define MILITARYCONQUEST_BATTLETEST_H

#include "gtest/gtest.h"
#include "../Classes/States/TurretState.h"
#include "../Classes/Elements/TurretGenerator.h"
#include "../Classes/Observers/EnemyLPObserver.h"

TEST(Battle, Battle) {
    // Initialization
    GAME_STATE game_state = GAME_STATE::game_difficulty_easy;

    sptr<Map> map = std::make_shared<Map>(MapEasy());

    sptr<Tower> tower = std::make_shared<Tower>(nullptr, 100, 100, nullptr);

    sptr<std::map<unsigned long long, sptr<Enemy>>> enemies = std::make_shared<std::map<unsigned long long, sptr<Enemy>>>();
    EnemyGenerator enemyGenerator(game_state, enemies, tower, {map}, true);
    enemyGenerator.genFixedNumber(ENEMY_TYPE::enemy1);

    enemyGenerator.tick(1001);

    Bullet bullet(0, 0, 5, {20, 100});

    for (std::pair<unsigned long long, sptr<Enemy>> tmp : *enemies) {
        tmp.second->move(20);
        sf::Vector2f pos = tmp.second->getPosition();
        bullet.checkCollision(enemies);
        EXPECT_EQ(tmp.second->getHP(), 70);
    }
}

#endif //MILITARYCONQUEST_BATTLETEST_H
