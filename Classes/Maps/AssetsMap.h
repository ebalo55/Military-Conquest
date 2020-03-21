//
// Created by ebalo on 14/03/20.
//

#ifndef TD_TOWERDEFENSE_ASSETSMAP_H
#define TD_TOWERDEFENSE_ASSETSMAP_H

#include <map>
#include <iostream>
#include <vector>

class AssetsMap {
private:
    static std::map<std::string, std::string> assets_map;

public:
    static std::string get(const std::string& asset_name);
    static void listNames();
    static void listPaths();
    static void listAll();
    static std::vector<std::string> listNamesAutomated();
    static std::vector<std::string> listPathsAutomated();
};

#endif //TD_TOWERDEFENSE_ASSETSMAP_H