//
// Created by ebalo on 02/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_TURRETTESTS_H
#define TD_TOWERDEFENSE_SFML_TURRETTESTS_H

#include "gtest/gtest.h"
#include "../Classes/Elements/Turret.h"
#include "../Classes/States/TurretState.h"
#include "../Classes/Elements/TurretGenerator.h"

class TurretTests : public ::testing::Test {
protected:
    GAME_STATE game_state = GAME_STATE::game_difficulty_easy;
    DrawableFactory factory;
    sf::Texture *texture;
    TurretGenerator *generator;
    Tower *tower;
    Turret *turret;
    MapEasy *map;
    sf::RenderWindow *window;
    EventHandler *event_handler;

    void SetUp() override {
        sf::VideoMode mode = sf::VideoMode::getDesktopMode();
        window = new sf::RenderWindow(sf::VideoMode(1, 1, mode.bitsPerPixel), "TD-TowerDefense", sf::Style::None);

        event_handler = new EventHandler(window, &game_state);
        map = new MapEasy();

        texture = factory.instantiateTexture("turret-tile", AssetsMap::get("tile-set"));

        tower = new Tower(nullptr, 100, 100, {
                {"heart", factory.instantiateSprite("heart", "heart")},
                {"coin", factory.instantiateSprite("coin", "coin")},
                {"hud-bg", factory.instantiateSprite("hud-bg", "hud-bg")}
        });

        turret = new Turret(tower, texture, 5,
                Turret::TurretStats {8,3,10,3,80,200,200,0,0,"Turret 1"},
                TURRET_TYPE::turret1);

        generator = new TurretGenerator(window, nullptr, event_handler, map, {turret});
    }

    void TearDown() override {
        delete generator;
        delete turret;
        delete tower;
        delete map;
        delete event_handler;
        delete window;
    }
};

TEST_F(TurretTests, Turret) {
    ASSERT_EQ(turret->getTower(), tower);

    EXPECT_EQ(turret->getLevel(), 1);
    EXPECT_EQ(turret->getPower(), 3);
    EXPECT_EQ(turret->getCost(), 10);
    EXPECT_EQ(turret->getUpgradeCost(), 8);
    EXPECT_EQ(turret->getFireRate(), 3);
    EXPECT_EQ((int)tower->getGold(), 100);

    tower->pay(turret->getUpgradeCost());
    turret->upgrade();
    EXPECT_EQ(turret->getLevel(), 2);
    // 3.99 as float expected but as the return value is an integer it is simply truncated to 3
    EXPECT_EQ(turret->getPower(), 3);
    // Cost should never be changed as the only value that change during the upgrade is upgrade_cost
    EXPECT_EQ(turret->getCost(), 10);
    // 10.08 as float expected, truncated to 10
    EXPECT_EQ(turret->getUpgradeCost(), 10);
    // 3.45 as float expected, truncated to 3
    EXPECT_EQ(turret->getFireRate(), 3);
    EXPECT_EQ((int)tower->getGold(), 92);

    tower->pay(turret->getUpgradeCost());
    turret->upgrade();
    EXPECT_EQ(turret->getLevel(), 3);
    // 5.31 as float expected, truncated to 5
    EXPECT_EQ(turret->getPower(), 5);
    // Cost should never be changed as the only value that change during the upgrade is upgrade_cost
    EXPECT_EQ(turret->getCost(), 10);
    // 12.70 as float expected, truncated to 12
    EXPECT_EQ(turret->getUpgradeCost(), 12);
    // 3.97 as float expected, truncated to 3
    EXPECT_EQ(turret->getFireRate(), 3);
    EXPECT_EQ((int)tower->getGold(), 82);

    tower->pay(turret->getUpgradeCost());
    turret->upgrade();
    EXPECT_EQ(turret->getLevel(), 4);
    // 7.06 as float expected, truncated to 7
    EXPECT_EQ(turret->getPower(), 7);
    // Cost should never be changed as the only value that change during the upgrade is upgrade_cost
    EXPECT_EQ(turret->getCost(), 10);
    // 16.00 as float expected, truncated to 16
    EXPECT_EQ(turret->getUpgradeCost(), 16);
    // 4.56 as float expected, truncated to 4
    EXPECT_EQ(turret->getFireRate(), 4);
    EXPECT_EQ((int)tower->getGold(), 70);
}

TEST_F(TurretTests, Generator) {
    int turret_number = 0;
    for(Turret *trt : *generator->getRegisteredTurrets()) { turret_number++; }
    EXPECT_EQ(turret_number, 0);

    // Maps position are not tested as the maps position are changed in events and not in the generator
    generator->registerTurret(generator->generate(TURRET_TYPE::turret1));
    turret_number = 0;
    for(Turret *trt : *generator->getRegisteredTurrets()) { turret_number++; }
    EXPECT_EQ(turret_number, 1);

    generator->registerTurret(generator->generate(TURRET_TYPE::turret1));
    turret_number = 0;
    for(Turret *trt : *generator->getRegisteredTurrets()) { turret_number++; }
    EXPECT_EQ(turret_number, 2);
}

#endif //TD_TOWERDEFENSE_SFML_TURRETTESTS_H
