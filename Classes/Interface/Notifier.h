//
// Created by ebalo on 16/03/20.
//

#ifndef TD_TOWERDEFENSE_NOTIFIER_H
#define TD_TOWERDEFENSE_NOTIFIER_H
#include <map>
#include "Observer.h"

class Notifier {
protected:
    std::map<unsigned long long, Observer *> observers;
public:
    virtual ~Notifier() {
        for(std::pair<unsigned long long, Observer *> line : observers) {
            delete line.second;
        }
    };

    virtual void notify() {
        for(std::pair<unsigned long long, Observer *> line : observers) {
            line.second->update();
        }
    };

    virtual void registerObserver(unsigned long long type_id, Observer *observer) { observers[type_id] = observer; }
    virtual void deleteObserver(unsigned long long type_id) { observers.erase(type_id); }
};

#endif //TD_TOWERDEFENSE_NOTIFIER_H
