//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENTKILL_WAVEOBSERVER_H
#define MILITARYCONQUEST_ACHIEVEMENTKILL_WAVEOBSERVER_H

#include <memory>
#include "../Interface/Observer.h"
#include "../Interface/Achievement.h"
#include "../Elements/WaveController.h"
#include "../Interface/AchievementObserver.h"

// Add a short alias for std::shared_ptr to the current environment
template<class T> using sptr = std::shared_ptr<T>;

class AchievementKill_WaveObserver : public AchievementObserver {
private:
    std::unique_ptr<Achievement> achievement;
public:
    AchievementKill_WaveObserver(std::unique_ptr<Achievement> achievement, OBSERVERS_TYPE_ID id,
                                 WaveController *wave_controller) : achievement(std::move(achievement)) {
        wave_controller->registerObserver(id, this);
    }

    void update(Method method, long long modificator) override {
        if (method == refresh || method == both) {
            achievement->update(modificator);
        }
        if (method == callback || method == both) {
            achievement->callback();
        }
    }
};

#endif //MILITARYCONQUEST_ACHIEVEMENTKILL_WAVEOBSERVER_H
