//
// Created by ebalo on 16/03/20.
//

#ifndef TD_TOWERDEFENSE_OBSERVER_H
#define TD_TOWERDEFENSE_OBSERVER_H

class Observer {
public:
    virtual ~Observer() {}
    virtual void update() = 0;
};

#endif //TD_TOWERDEFENSE_OBSERVER_H
