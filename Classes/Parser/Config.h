//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_CONFIG_H
#define MILITARYCONQUEST_CONFIG_H

#include <nlohmann/json.hpp>
#include <memory>
#include <fstream>
#include "../Maps/AssetsMap.h"
#include "../States/TurretStats.h"
#include "../States/EnemyStats.h"
#include "../States/AchievementInfos.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class Config {
private:
    static sptr<Config> instance;
    std::map<std::string, int> turret_type;
    std::map<std::string, int> enemy_type;

    static nlohmann::json json;

    Config();

    static std::vector<int> getTypesIndex(bool enemy = true);

    std::vector<std::pair<bool, int>> getWaveTemplate(const std::string &tree, const std::string &values);

    nlohmann::json computeBase(const std::string &tree, nlohmann::json starting_point = json);

    std::vector<std::string> explode(const std::string &string, char delimiter);

public:
    static sptr<Config> getInstance();

    static std::map<std::string, int> getLoopableTurretType();

    static int getTurretType(std::string name);

    static int getLoadedTurretNumber();

    static std::map<std::string, int> getLoopableEnemyType();

    static int getEnemyType(std::string name);

    static int getLoadedEnemyNumber();

    static std::vector<int> getAllEnemiesType();

    static std::vector<int> getAllBossesType();

    static int getWidth();

    static int getHeight();

    void printConfig();

    TurretStats getTurretStats(int turret_type);

    TurretStats getTurretStats(std::string turret_name);

    std::vector<TurretStats> getAllTurretStats();

    EnemyStats getEnemyStats(int enemy_type);

    std::vector<EnemyStats> getAllEnemyStats();

    bool isBoss(int enemy_type);

    std::vector<std::pair<bool, int>> getEnemyWaveTemplate();

    std::vector<std::pair<bool, int>> getBossWaveTemplate();

    std::vector<AchievementInfo> getAchievements();
};

#endif //MILITARYCONQUEST_CONFIG_H
