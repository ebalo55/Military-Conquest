//
// Created by ebalo on 30/03/20.
//

#include "gtest/gtest.h"
#include "MapTests.h"
#include "DrawableFactoryTest.h"
#include "EnemyTests.h"
#include "TurretTests.h"
#include "parserTests.h"
#include "battleTest.h"
#include "ConfigParserTests.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
