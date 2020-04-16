//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_ENEMYSTATS_H
#define MILITARYCONQUEST_ENEMYSTATS_H

struct EnemyStats {
    double hp,
        velocity,
        acceleration,
        power,
        easy_gen_time,
        hard_gen_time;

    int tile_index,
        identifier;
    bool animated;
    int animation_tile,
        animation_time;

    EnemyStats& operator*=(double r) {
        hp *= r;
        power *= r;
        return *this;
    }
    EnemyStats& operator*(double r) {
        hp *= r;
        power *= r;
        return *this;
    }
    bool operator==(const EnemyStats& r) {
        return hp == r.hp && power == r.power && velocity == r.velocity && acceleration == r.acceleration &&
               easy_gen_time == r.easy_gen_time && hard_gen_time == r.hard_gen_time;
    }
    bool operator==(const EnemyStats& r) const {
        return hp == r.hp && power == r.power && velocity == r.velocity && acceleration == r.acceleration &&
               easy_gen_time == r.easy_gen_time && hard_gen_time == r.hard_gen_time;
    }
    friend std::ostream& operator<<(std::ostream& os, const EnemyStats& es) {
        return os << "----------" <<
            "\n\tHp: \t\t\t\t\t" << es.hp <<
            "\n\tvelocity: \t\t\t\t" << es.velocity <<
            "\n\tacceleration: \t\t\t" << es.acceleration <<
            "\n\tpower: \t\t\t\t\t" << es.power <<
            "\n\teasy-generation-time: \t" << es.easy_gen_time <<
            "\n\thard-generation-time: \t" << es.hard_gen_time;
    }
};

#endif //MILITARYCONQUEST_ENEMYSTATS_H
