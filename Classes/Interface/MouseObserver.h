//
// Created by ebalo on 16/03/20.
//

#ifndef TD_TOWERDEFENSE_MOUSEOBSERVER_H
#define TD_TOWERDEFENSE_MOUSEOBSERVER_H

#include "../States/MouseStates.h"
#include "Observer.h"

class MouseObserver : public Observer {
public:
    virtual ~MouseObserver() {}
    void update() {};
    virtual void update(OBSERVERS_TYPE_ID ev_type) = 0;
};

#endif //TD_TOWERDEFENSE_MOUSEOBSERVER_H
