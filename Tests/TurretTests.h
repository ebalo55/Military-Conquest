//
// Created by ebalo on 02/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_TURRETTESTS_H
#define TD_TOWERDEFENSE_SFML_TURRETTESTS_H

#include "gtest/gtest.h"
#include "../Classes/States/TurretState.h"
#include "../Classes/Elements/TurretGenerator.h"

class TurretTests : public ::testing::Test {
protected:
    GAME_STATE game_state = GAME_STATE::game_difficulty_easy;
    DrawableFactory factory;
    sptr<sf::Texture> texture;
    TurretGenerator *generator;
    sptr<Tower> tower;
    sptr<Turret> turret;
    sptr<Map> map;
    sptr<sf::RenderWindow> window;
    sptr<EventHandler> event_handler;

    void SetUp() override {
        sf::VideoMode mode = sf::VideoMode::getDesktopMode();
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1, 1, mode.bitsPerPixel), "TD-TowerDefense", sf::Style::None);

        event_handler = std::make_shared<EventHandler>(window, std::make_shared<GAME_STATE>(game_state));
        map = std::make_shared<Map>(MapEasy());

        texture = factory.instantiateTexture("turret-tile", AssetsMap::get("tile-set"));

        tower = std::make_shared<Tower>(nullptr, 100, 100, nullptr);

        turret = std::make_shared<Turret>(tower, texture, Config::getInstance()->getTurretStats(0));

        generator = new TurretGenerator(window, nullptr, event_handler, map, true, tower);
    }

    void TearDown() override {
        delete generator;
        turret.reset();
        tower.reset();
        map.reset();
        event_handler.reset();
        window.reset();
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
    EXPECT_EQ(turret->getPower(), 3);
    // Cost should never be changed as the only value that change during the upgrade is upgrade_cost
    EXPECT_EQ(turret->getCost(), 10);
    EXPECT_EQ(turret->getUpgradeCost(), 14);
    EXPECT_EQ(turret->getFireRate(), 3);
    EXPECT_EQ((int)tower->getGold(), 92);

    tower->pay(turret->getUpgradeCost());
    turret->upgrade();
    EXPECT_EQ(turret->getLevel(), 3);
    EXPECT_EQ(turret->getPower(), 4);
    // Cost should never be changed as the only value that change during the upgrade is upgrade_cost
    EXPECT_EQ(turret->getCost(), 10);
    EXPECT_EQ(turret->getUpgradeCost(), 24);
    EXPECT_EQ(turret->getFireRate(), 3);
    EXPECT_EQ((int)tower->getGold(), 78);

    tower->pay(turret->getUpgradeCost());
    turret->upgrade();
    EXPECT_EQ(turret->getLevel(), 4);
    EXPECT_EQ(turret->getPower(), 6);
    // Cost should never be changed as the only value that change during the upgrade is upgrade_cost
    EXPECT_EQ(turret->getCost(), 10);
    EXPECT_EQ(turret->getUpgradeCost(), 42);
    EXPECT_EQ(turret->getFireRate(), 4);
    EXPECT_EQ((int)tower->getGold(), 54);
}

TEST_F(TurretTests, Generator) {
    int turret_number = 0;
    for(sptr<Turret> trt : *generator->getRegisteredTurrets()) { turret_number++; }
    EXPECT_EQ(turret_number, 0);

    // Maps position are not tested as the maps position are changed in events and not in the generator
    generator->registerTurret(generator->generate(TURRET_TYPE::turret1));
    turret_number = 0;
    for(sptr<Turret> trt : *generator->getRegisteredTurrets()) { turret_number++; }
    EXPECT_EQ(turret_number, 1);

    generator->registerTurret(generator->generate(TURRET_TYPE::turret1));
    turret_number = 0;
    for(sptr<Turret> trt : *generator->getRegisteredTurrets()) { turret_number++; }
    EXPECT_EQ(turret_number, 2);
}

#endif //TD_TOWERDEFENSE_SFML_TURRETTESTS_H
