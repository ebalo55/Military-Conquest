//
// Created by ebalo on 22/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_MOVEMENT_H
#define TD_TOWERDEFENSE_SFML_MOVEMENT_H

#include <cmath>

class Movement {
protected:
    double vx = 0,
        vy = 0,
        ax = 0,
        ay = 0;
public:
    Movement() {};

    virtual void move(size_t time_step) = 0;

    double getVx() const { return vx; };
    void setVx(double vx) { this->vx = vx; };
    double getVy() const { return vy; };
    void setVy(double vy) { this->vy = vy; };
    void setVelocity(double vx, double vy) { this->vx = vx; this->vy = vy; };
    void setVelocity(double velocity) { this->vx = velocity; this->vy = velocity; };

    double getAx() const { return ax; };
    void setAx(double ax) { this->ax = ax; };
    double getAy() const { return ay; };
    void setAy(double ay) { this->ay = ay; };
    void setAcceleration(double ax, double ay) { this->ax = ax; this->ay = ay; };
    void setAcceleration(double acceleration) { this->ax = acceleration; this->ay = acceleration; };
};

#endif //TD_TOWERDEFENSE_SFML_MOVEMENT_H
