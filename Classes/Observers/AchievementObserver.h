//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENTOBSERVER_H
#define MILITARYCONQUEST_ACHIEVEMENTOBSERVER_H

#include <memory>
#include "../Interface/Observer.h"
#include "../Interface/Achievement.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class AchievementObserver : public Observer {
private:
    sptr<Achievement> achievement;
public:
    AchievementObserver(sptr<Achievement> achievement) :achievement(achievement) {}

    void update() {
        achievement->callback();
    }
};

#endif //MILITARYCONQUEST_ACHIEVEMENTOBSERVER_H
