//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENTNOTIFIER_H
#define MILITARYCONQUEST_ACHIEVEMENTNOTIFIER_H

#include "Notifier.h"
#include "../Interface/AchievementObserver.h"
#include "../Elements/Turret.h"

class AchievementNotifier : public Notifier {
private:
    void notify() override {};
    virtual void registerObserver(unsigned long long type_id, Observer *observer) override {}
protected:
    std::map<unsigned long long, AchievementObserver *> observers;
public:
    virtual ~AchievementNotifier() {
        for(std::pair<unsigned long long, AchievementObserver *> line : observers) {
            delete line.second;
        }
    };

    virtual void
    registerObserver(unsigned long long type_id, AchievementObserver *observer) { observers[type_id] = observer; }

    virtual void deleteObserver(unsigned long long type_id) override { observers.erase(type_id); }

    void notify(long long id, AchievementObserver::Method method, long long modificator = 0) {
        for(std::pair<unsigned long long, AchievementObserver *> line : observers) {
            if(id == line.first || id == -1) {
                line.second->update(method, modificator);
            }
        }
    }


};

#endif //MILITARYCONQUEST_ACHIEVEMENTNOTIFIER_H
