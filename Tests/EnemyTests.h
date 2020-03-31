//
// Created by ebalo on 31/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_ENEMYTESTS_H
#define TD_TOWERDEFENSE_SFML_ENEMYTESTS_H

#include "gtest/gtest.h"
#include "../Classes/Elements/Enemy.h"
#include "../Classes/States/EnemyState.h"
#include "../Classes/Elements/EnemyGenerator.h"

class EnemyTests : public ::testing::Test {
protected:
    GAME_STATE game_state = GAME_STATE::game_difficulty_easy;
    DrawableFactory factory;
    sf::Texture *texture;
    Enemy *enemy;
    EnemyGenerator *generator;
    std::forward_list<Enemy *> enemies;
    Tower *tower;
    MapEasy *map;

    void SetUp() override {
        texture = factory.instantiateTexture("enemies", AssetsMap::get("enemies-tile-set"));
        map = new MapEasy();
        enemy = new Enemy(map, true, texture, 0, Enemy::Stats {75, 100, 0, 13, 100, 100}, ENEMY_TYPE::enemy1);
        tower = new Tower(nullptr, 100, 100, {
                {"heart", factory.instantiateSprite("heart", "heart")},
                {"coin", factory.instantiateSprite("coin", "coin")},
                {"hud-bg", factory.instantiateSprite("hud-bg", "hud-bg")}
        });
        generator = new EnemyGenerator(game_state, &enemies, tower, {enemy});
    }

    void TearDown() override {
        delete generator;
        delete tower;
        delete enemy;
        delete map;
    }
};

TEST_F(EnemyTests, Enemy) {
    EXPECT_EQ(enemy->isMapEasy(), true);
    EXPECT_EQ(enemy->isAnimated(), false);
    EXPECT_EQ(enemy->getAnimationIndex(), 0);
    EXPECT_EQ(enemy->getAnimationTime(), 100);
    // Origin is 0, 80 but the position is returned rounded up by enemy_size (= 20)
    EXPECT_EQ(enemy->getPosition(), (sf::Vector2f{20, 100}));
    /* Time is in millis this correspond to the formula:
     *      velocity / 1000 * time_lapse
     * In this case the result is 1px
     */
    enemy->move(10);
    EXPECT_EQ(enemy->getPosition(), (sf::Vector2f{21, 100}));
    EXPECT_EQ(enemy->getHP(), 75);
    enemy->hit(1);
    EXPECT_EQ(enemy->getHP(), 74);
    enemy->setHP(80);
    enemy->setPower(20);
    enemy->upgrade();
    EXPECT_EQ(enemy->getHP(), 100);
    EXPECT_EQ(enemy->getPower(), 25);
}

TEST_F(EnemyTests, Generator) {
    generator->genFixedNumber(ENEMY_TYPE::enemy1, 2);
    generator->tick(101);
    int x = 0;
    for(Enemy *tmp : enemies) { x++; }
    EXPECT_EQ(x, 1);

    generator->tick(101);
    x = 0;
    for(Enemy *tmp : enemies) { x++; }
    EXPECT_EQ(x, 2);
}

#endif //TD_TOWERDEFENSE_SFML_ENEMYTESTS_H