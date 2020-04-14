//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENT_H
#define MILITARYCONQUEST_ACHIEVEMENT_H

#include "../Elements/Turret.h"

class Achievement {
protected:
    unsigned long long goal;

public:
    Achievement(unsigned long long goal) :goal(goal) {}

    virtual void callback() = 0;
    template<class type> void update(type modifier) {};
};

#endif //MILITARYCONQUEST_ACHIEVEMENT_H
