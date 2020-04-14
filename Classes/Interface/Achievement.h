//
// Created by ebalo on 14/04/20.
//

#ifndef MILITARYCONQUEST_ACHIEVEMENT_H
#define MILITARYCONQUEST_ACHIEVEMENT_H

#include "Event.h"

class Achievement {
protected:
    unsigned long long goal;
public:
    Achievement(unsigned long long goal) :goal(goal) {}

    virtual void callback() = 0;
};

#endif //MILITARYCONQUEST_ACHIEVEMENT_H
