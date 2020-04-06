//
// Created by ebalo on 02/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BULLET_H
#define TD_TOWERDEFENSE_SFML_BULLET_H


#include "Enemy.h"

class Bullet : public sf::Drawable, public sf::Transformable {
private:
    int vx,
        vy,
        power;

    sf::CircleShape bullet;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Bullet(int vx, int vy, int power, sf::Vector2f origin);

    void move(int time_lapse);
};


#endif //TD_TOWERDEFENSE_SFML_BULLET_H
