//
// Created by ebalo on 02/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BULLET_H
#define TD_TOWERDEFENSE_SFML_BULLET_H


#include "Enemy.h"

class Bullet : public sf::Drawable, public sf::Transformable, {
private:
    int velocity,
        acceleration,
        power;

    sf::CircleShape bullet;

    Enemy *victim;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Bullet(int velocity, int acceleration, int power, Enemy *victim, sf::Vector2f origin);

    void move(int time_lapse);
};


#endif //TD_TOWERDEFENSE_SFML_BULLET_H
