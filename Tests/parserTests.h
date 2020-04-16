//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_PARSERTESTS_H
#define MILITARYCONQUEST_PARSERTESTS_H

#include "gtest/gtest.h"
#include "../Classes/Parser/MapParser.h"
#include "../Classes/Maps/AssetsMap.h"

TEST(Parser, MapParse) {
    int *map = MapParser::parse(AssetsMap::get("map-easy"), 640);
    delete[] map;
}

TEST(Parser, VariationParse) {
    int *map = MapParser::parse(AssetsMap::get("map-hard"), 640);
    std::vector<int *> paths = MapParser::parseVariation(AssetsMap::get("map-hard"), 640);

    delete[] map;
    paths.clear();
}

#endif //MILITARYCONQUEST_PARSERTESTS_H
