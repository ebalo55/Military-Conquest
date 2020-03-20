//
// Created by ebalo on 14/03/20.
//

#include "AssetsMap.h"

std::map<std::string, std::string> AssetsMap::assets_map = {
        {"tile-set", "Assets/tile-set.png"},
};

std::string AssetsMap::get(const std::string& asset_name) { return assets_map.at(asset_name); }

void AssetsMap::listNames() {
    std::cout << "Available assets name:" << std::endl;
    for(std::pair<std::string, std::string> line : assets_map) {
        std::cout << "\t- " << line.first << std::endl;
    }
}

void AssetsMap::listPaths() {
    std::cout << "Listed paths are:" << std::endl;
    for(std::pair<std::string, std::string> line : assets_map) {
        std::cout << "\t- " << line.second << std::endl;
    }
}

void AssetsMap::listAll() {
    std::cout << "Available assets are:" << std::endl;
    for(std::pair<std::string, std::string> line : assets_map) {
        std::cout << "\t- named: '" << line.first << "', loads: '" << line.second << "'" << std::endl;
    }
}

std::vector<std::string> AssetsMap::listNamesAutomated() {
    std::vector<std::string> result;
    result.reserve(assets_map.size());

    for(std::pair<std::string, std::string> line : assets_map) { result.push_back(line.first); }
    return result;
}

std::vector<std::string> AssetsMap::listPathsAutomated() {
    std::vector<std::string> result;
    result.reserve(assets_map.size());

    for(std::pair<std::string, std::string> line : assets_map) { result.push_back(line.second); }
    return result;
}
