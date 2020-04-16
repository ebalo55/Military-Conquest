//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_MAPEASY_H
#define TD_TOWERDEFENSE_SFML_MAPEASY_H

#include "Map.h"

class MapEasy : public Map {
public:
    MapEasy() : Map() {
        map = MapParser::parse(AssetsMap::get("map-easy"), map_width * map_height);
        generate(sf::Vector2u(40, 40), map, map_width, map_height);
    }
};

#endif //TD_TOWERDEFENSE_SFML_MAPEASY_H
