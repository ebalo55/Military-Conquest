//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_MAPHARD_H
#define TD_TOWERDEFENSE_SFML_MAPHARD_H

#include "Map.h"

class MapHard : public Map {
    std::vector<int *> paths;
public:
    MapHard() : Map() {
        int size = map_width * map_height;
        map = MapParser::parse(AssetsMap::get("map-hard"), size);
        paths = MapParser::parseVariation(AssetsMap::get("map-hard"), size);
        generate(sf::Vector2u(40, 40), map, map_width, map_height);
    }
    
    int *getPath(int index) { return paths[index]; }
    int getPathsSize() { return paths.size(); }
};

#endif //TD_TOWERDEFENSE_SFML_MAPHARD_H
