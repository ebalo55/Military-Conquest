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

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class Config {
private:
    static sptr<Config> instance;
    std::map<std::string, int> turret_type;
    std::map<std::string, int> enemy_type;

    nlohmann::json json;

    Config();
public:
    static sptr<Config> getInstance();
    static std::map<std::string, int> getLoopableTurretType();
    static int getTurretType(std::string name);
    static std::map<std::string, int> getLoopableEnemyType();
    static int getEnemyType(std::string name);

    void printConfig();

    TurretStats getTurretStats(int turret_type);
    TurretStats getTurretStats(std::string turret_name);
    std::vector<TurretStats> getAllTurretStats();

    EnemyStats getEnemyStats(int enemy_type);
    std::vector<EnemyStats> getAllEnemyStats();
};

#endif //MILITARYCONQUEST_CONFIG_H
