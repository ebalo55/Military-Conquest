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
    void update() override {}
public:
    AchievementObserver(sptr<Achievement> achievement) :achievement(achievement) {}

    enum Method {
        refresh,
        callback,
        both
    };

    void update(Method method, long long modificator = 0) {
        if(method == refresh || method == both) {
            achievement->update(modificator);
        }
        if(method == callback || method == both) {
            achievement->callback();
        }
    }
};

#endif //MILITARYCONQUEST_ACHIEVEMENTOBSERVER_H
