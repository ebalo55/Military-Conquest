//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_CONFIGPARSERTESTS_H
#define MILITARYCONQUEST_CONFIGPARSERTESTS_H
#include "gtest/gtest.h"
#include "../Classes/Parser/Config.h"

class ConfigTest : public ::testing::Test {
protected:
    sptr<Config> config;
public:
    void SetUp() override {
        config = Config::getInstance();
    }

    void TearDown() override {
        config.reset();
    }
};

/*TEST_F(ConfigTest, Parser) {
    config->printConfig();
}*/

TEST_F(ConfigTest, TurretStats) {
    TurretStats stats{8, 5, 10, 3, 80, "Turret 1"};
    TurretStats result = config->getTurretStats(0);
    EXPECT_EQ(stats, result);

    result = config->getTurretStats("Turret 1");
    EXPECT_EQ(stats, result);
    result *= 1.5;
    std::cout << result << std::endl << std::endl;

    std::vector<TurretStats> vector = config->getAllTurretStats();
    for (const TurretStats &ts : vector) {
        std::cout << ts << std::endl;
    }
}

TEST_F(ConfigTest, EnemyStats) {
    EnemyStats stats{75, 135, 0, 13, 900, 800};
    EnemyStats result = config->getEnemyStats(0);
    EXPECT_EQ(stats, result);

    result *= 1.5;
    std::cout << result << std::endl << std::endl;

    std::vector<EnemyStats> vector = config->getAllEnemyStats();
    for(EnemyStats es : vector) {
        std::cout << es << std::endl;
    }
}

#endif //MILITARYCONQUEST_CONFIGPARSERTESTS_H
