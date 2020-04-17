//
// Created by ebalo on 17/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENTINFOS_H
#define MILITARYCONQUEST_ACHIEVEMENTINFOS_H

#include "ObserversTypeId.h"
#include <vector>
#include <string>

struct AchievementInfo {
    AchievementInfo(OBSERVERS_TYPE_ID id, std::vector<std::string> names, int goal, double up_factor) {
        type = id;
        this->names = names;
        first_goal = goal;
        upgrade_factor = up_factor;
    }

    OBSERVERS_TYPE_ID type;
    std::vector<std::string> names;
    int first_goal;
    double upgrade_factor;
};

#endif //MILITARYCONQUEST_ACHIEVEMENTINFOS_H
