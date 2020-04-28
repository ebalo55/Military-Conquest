//
// Created by ebalo on 28/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENTOBSERVER_H
#define MILITARYCONQUEST_ACHIEVEMENTOBSERVER_H

class AchievementObserver {
public:
    enum Method {
        refresh,
        callback,
        both
    };

    virtual ~AchievementObserver() {};

    virtual void update(Method method, long long modificator) = 0;
};

#endif //MILITARYCONQUEST_ACHIEVEMENTKILL_WAVEOBSERVER_H
