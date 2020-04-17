//
// Created by ebalo on 02/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_BULLET_H
#define TD_TOWERDEFENSE_SFML_BULLET_H

#include <memory>
#include <forward_list>
#include "Enemy.h"
#include "../Parser/Config.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class Bullet : public sf::Drawable, public sf::Transformable {
private:
    double vx,
        vy;
    int power;

    sf::CircleShape bullet;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Bullet(double vx, double vy, int power, sf::Vector2f origin);

    void move(int time_lapse);
    bool checkCollision(const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies);
    bool isOutOfMap();
};


#endif //TD_TOWERDEFENSE_SFML_BULLET_H
