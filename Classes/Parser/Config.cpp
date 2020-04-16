//
// Created by ebalo on 16/04/20.
//
#include "Config.h"

sptr<Config> Config::instance = nullptr;

Config::Config() {
    std::fstream handle(AssetsMap::get("config"), std::fstream::in);

    // load the json file into the json instance
    handle >> json;

    // Load the path to the enemy and turret tileset
    AssetsMap::override("enemies-tile-set", json["enemies"]["tile-name"]);
    AssetsMap::override("tile-set", json["turrets"]["tile-name"]);

    // Fill the map of turrets name and identifier
    for(nlohmann::json fragment : json["turrets"]["types"]) {
        int id = fragment["identifier"];
        turret_type.emplace("turret-" + std::to_string(id), id);
    }

    // Fill the map of enemies name and identifier
    for(nlohmann::json fragment : json["enemies"]["types"]) {
        int id = fragment["identifier"];
        enemy_type.emplace("enemy-" + std::to_string(id), id);
    }
}

sptr<Config> Config::getInstance() {
    if(instance == nullptr) {
        instance = std::make_shared<Config>(Config());
    }
    return instance;
}

void Config::printConfig() {
    std::cout << std::setw(5) << json << std::endl;
}

TurretStats Config::getTurretStats(int turret_type) {
    if(turret_type >= json["turrets"]["types"].size()) {
        throw std::runtime_error("Requested a turret index that does not exist in the configuration.");
    }

    nlohmann::json step = json["turrets"]["types"][turret_type]["stats"];

    TurretStats stats {
        step["upgrade-cost"],
        step["power"],
        step["cost"],
        step["fire-rate"],
        step["radius"],
        json["turrets"]["types"][turret_type]["name"],
        json["turrets"]["types"][turret_type]["tile-index"],
        turret_type
    };
    return stats;
}

TurretStats Config::getTurretStats(std::string turret_name) {
    int position;
    for(position = 0; position < json["turrets"]["types"].size(); position++) {
        if(json["turrets"]["types"][position]["name"] == turret_name) {
            break;
        }
    }

    if(position >= json["turrets"]["types"].size()) {
        throw std::runtime_error("Requested a turret name that does not match any name in the configuration.");
    }

    return getTurretStats(position);
}

std::vector<TurretStats> Config::getAllTurretStats() {
    std::vector<TurretStats> result;

    for(nlohmann::json fragment : json["turrets"]["types"]) {
        nlohmann::json step = fragment["stats"];
        result.push_back({
            step["upgrade-cost"],
            step["power"],
            step["cost"],
            step["fire-rate"],
            step["radius"],
            fragment["name"],
            fragment["tile-index"],
            fragment["identifier"]
        });
    }

    return result;
}

EnemyStats Config::getEnemyStats(int enemy_type) {
    if(enemy_type >= json["enemies"]["types"].size()) {
        throw std::runtime_error("Requested an enemy index that does not exist in the configuration.");
    }

    nlohmann::json step = json["enemies"]["types"][enemy_type]["stats"];
    bool animated = !json["enemies"]["types"][enemy_type]["animated"].is_boolean();

    EnemyStats stats {
            step["hp"],
            step["velocity"],
            step["acceleration"],
            step["power"],
            step["generation-time"]["easy"],
            step["generation-time"]["hard"],
            json["turrets"]["types"][enemy_type]["tile-index"],
            enemy_type,
            animated,
            animated ? (int)json["enemies"]["types"][enemy_type]["animated"]["tile-index"] : 0,
            animated ? (int)json["enemies"]["types"][enemy_type]["animated"]["frame-time"] : 0
    };
    return stats;
}

std::vector<EnemyStats> Config::getAllEnemyStats() {
    std::vector<EnemyStats> result;

    for(nlohmann::json fragment : json["enemies"]["types"]) {
        nlohmann::json step = fragment["stats"];
        bool animated = !fragment["animated"].is_boolean();
        result.push_back({
            step["hp"],
            step["velocity"],
            step["acceleration"],
            step["power"],
            step["generation-time"]["easy"],
            step["generation-time"]["hard"],
            fragment["tile-index"],
            fragment["identifier"],
            animated,
            animated ? (int)fragment["animated"]["tile-index"] : 0,
            animated ? (int)fragment["animated"]["frame-time"] : 0
        });
    }

    return result;
}

int Config::getTurretType(std::string name) {
    return instance->turret_type[name];
}

int Config::getEnemyType(std::string name) {
    return instance->enemy_type[name];
}

std::map<std::string, int> Config::getLoopableTurretType() {
    return instance->turret_type;
}

std::map<std::string, int> Config::getLoopableEnemyType() {
    return instance->enemy_type;
}