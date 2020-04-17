//
// Created by ebalo on 16/04/20.
//
#include "Config.h"

sptr<Config> Config::instance = nullptr;
nlohmann::json Config::json = nullptr;

Config::Config() {
    // Load the path to the enemy and turret tileset
    AssetsMap::override("enemies-tile-set", json["enemies"]["tile-name"]);
    AssetsMap::override("tile-set", json["turrets"]["tile-name"]);

    // Fill the map of turrets name and identifier
    for (nlohmann::json fragment : computeBase("turrets.types")) {
        int id = fragment["identifier"];
        turret_type.emplace("turret-" + std::to_string(id), id);
    }

    // Fill the map of enemies name and identifier
    for (nlohmann::json fragment : computeBase("enemies.types")) {
        int id = fragment["identifier"];
        enemy_type.emplace("enemy-" + std::to_string(id), id);
    }
}

sptr<Config> Config::getInstance() {
    if(instance == nullptr) {
        std::fstream handle(AssetsMap::get("config"), std::fstream::in);
        // load the json file into the json instance
        handle >> json;

        instance = std::make_shared<Config>(Config());
    }
    return instance;
}

void Config::printConfig() {
    std::cout << std::setw(5) << json << std::endl;
}

TurretStats Config::getTurretStats(int turret_type) {
    if (turret_type >= json["turrets"]["types"].size()) {
        throw std::runtime_error("Requested a turret index that does not exist in the configuration.");
    }

    nlohmann::json base = computeBase("turrets.types." + std::to_string(turret_type)),
            step = computeBase("stats", base);

    TurretStats stats{
            step["upgrade-cost"],
            step["power"],
            step["cost"],
            step["fire-rate"],
            step["radius"],
            base["name"],
            base["tile-index"],
            turret_type
    };
    return stats;
}

TurretStats Config::getTurretStats(std::string turret_name) {
    int position;
    nlohmann::json base = computeBase("turrets.types");
    for (position = 0; position < base.size(); position++) {
        if (base[position]["name"] == turret_name) {
            break;
        }
    }

    if (position >= base.size()) {
        throw std::runtime_error("Requested a turret name that does not match any name in the configuration.");
    }

    return getTurretStats(position);
}

std::vector<TurretStats> Config::getAllTurretStats() {
    std::vector<TurretStats> result;

    for (nlohmann::json fragment : computeBase("turrets.types")) {
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
    nlohmann::json base = computeBase("enemies.types");
    if (enemy_type >= base.size()) {
        throw std::runtime_error("Requested an enemy index that does not exist in the configuration.");
    }

    base = computeBase(std::to_string(enemy_type), base);
    nlohmann::json step = base["stats"];
    bool animated = !base["animated"].is_boolean();

    EnemyStats stats{
            step["hp"],
            step["velocity"],
            step["acceleration"],
            step["power"],
            step["generation-time"]["easy"],
            step["generation-time"]["hard"],
            base["tile-index"],
            enemy_type,
            animated,
            animated ? (int) base["animated"]["tile-index"] : 0,
            animated ? (int) base["animated"]["frame-time"] : 0
    };
    return stats;
}

std::vector<EnemyStats> Config::getAllEnemyStats() {
    std::vector<EnemyStats> result;

    for (nlohmann::json fragment : computeBase("enemies.types")) {
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
                                 animated ? (int) fragment["animated"]["tile-index"] : 0,
                                 animated ? (int) fragment["animated"]["frame-time"] : 0
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

int Config::getLoadedTurretNumber() {
    return instance->turret_type.size();
}

int Config::getLoadedEnemyNumber() {
    return instance->enemy_type.size();
}

bool Config::isBoss(int enemy_type) {
    nlohmann::json base = computeBase("enemies.types");
    if (enemy_type >= base.size()) {
        throw std::runtime_error("Requested an enemy index that does not exist in the configuration.");
    }
    return base[enemy_type]["boss"];
}

std::vector<int> Config::getTypesIndex(bool enemy) {
    std::vector<int> result;

    for (std::pair<std::string, int> line : instance->enemy_type) {
        if (enemy == !instance->isBoss(line.second)) {
            result.push_back(line.second);
        }
    }

    return result;
}

std::vector<int> Config::getAllEnemiesType() {
    return getTypesIndex();
}

std::vector<int> Config::getAllBossesType() {
    return getTypesIndex(false);
}

std::vector<std::pair<bool, int>> Config::getWaveTemplate(const std::string &tree, const std::string &values) {
    std::vector<std::pair<bool, int>> result;
    std::vector<std::string> required_values = explode(values, ',');

    for (nlohmann::json fragment : computeBase(tree)) {
        result.emplace_back(fragment[required_values[0]], fragment[required_values[1]]);
    }

    return result;
}

std::vector<std::pair<bool, int>> Config::getEnemyWaveTemplate() {
    return getWaveTemplate("enemies.enemy-wave-template", "timed,amount");
}

std::vector<std::pair<bool, int>> Config::getBossWaveTemplate() {
    return getWaveTemplate("enemies.boss-wave-template", "timed,amount");
}

std::vector<AchievementInfo> Config::getAchievements() {
    std::vector<AchievementInfo> result;

    for (nlohmann::json fragment : json["achievements"]) {
        std::vector<std::string> names;

        for (std::string name : fragment["names"]) {
            names.push_back(name);
        }

        result.emplace_back(
                fragment["type"] == "kills" ? OBSERVERS_TYPE_ID::killed_enemies : OBSERVERS_TYPE_ID::survived_waves,
                names, fragment["first-goal"], fragment["upgrade-factor"]);
    }

    return result;
}

std::vector<std::string> Config::explode(const std::string &string, const char delimiter) {
    std::vector<std::string> result;
    std::istringstream iss(string);

    for (std::string fragment; std::getline(iss, fragment, delimiter);) {
        if (!fragment.empty()) {
            result.push_back(fragment);
        }
    }

    return result;
}

nlohmann::json Config::computeBase(const std::string &tree, nlohmann::json starting_point) {
    nlohmann::json base = starting_point;
    for (const std::string &part : explode(tree, '.')) {
        base = base[part];
    }

    return base;
}

int Config::getWidth() {
    return json["window"]["width"];
}

int Config::getHeight() {
    return json["window"]["height"];
}
