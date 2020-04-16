//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_TURRETSTATS_H
#define MILITARYCONQUEST_TURRETSTATS_H

#include <string>

struct TurretStats {
    int upgrade_cost,
            power,
            cost,
            fire_rate,
            radius;

    std::string name;
    int tile_index,
        identifier;

    TurretStats& operator*=(double r) {
        cost *= r;
        upgrade_cost *= r;
        return *this;
    }
    TurretStats& operator*(double r) {
        cost *= r;
        upgrade_cost *= r;
        return *this;
    }
    bool operator==(const TurretStats& r) {
        return upgrade_cost == r.upgrade_cost && power == r.power && cost == r.cost && fire_rate == r.fire_rate &&
            radius == r.radius;
    }
    bool operator==(const TurretStats& r) const {
        return upgrade_cost == r.upgrade_cost && power == r.power && cost == r.cost && fire_rate == r.fire_rate &&
               radius == r.radius;
    }
    friend std::ostream& operator<<(std::ostream& os, const TurretStats& ts) {
        return os << "----------" <<
            "\n\tupgrade-cost: \t" << ts.upgrade_cost <<
            "\n\tpower: \t\t\t" << ts.power <<
            "\n\tcost: \t\t\t" << ts.cost <<
            "\n\tfire-rate: \t\t" << ts.fire_rate <<
            "\n\tradius: \t\t" << ts.radius <<
            "\n\tname: \t\t\t" << ts.name;
    }
};

#endif //MILITARYCONQUEST_TURRETSTATS_H
