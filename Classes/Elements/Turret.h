//
// Created by michelangelo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_TURRET_H
#define TD_TOWERDEFENSE_TURRET_H

#include <SFML/Graphics.hpp>
#include "../Interface/Notifier.h"
#include "Tower.h"
#include "../States/TurretState.h"
#include "Enemy.h"

class Turret : public sf::Drawable, public sf::Transformable, public Notifier {
private:
    double upgrade_cost = 1,
        power = 1,
        cost = 1,
        fire_rate = 1,

        bullet_vx = 0,
        bullet_vy = 0,
        bullet_ax = 0,
        bullet_ay = 0;

    int level = 1,
        radius = 1;

    TURRET_TYPE hashcode;

    Tower *tower;
    std::string name;
    sf::Sprite sprite;
    sf::Clock clock;

    Enemy *victim = nullptr;

    double upgrade_factor_cost = 1.26,          // 26% upgrade
        upgrade_factor_power = 1.33,            // 33% upgrade
        upgrade_factor_fire_rate = 1.15;        // 15% upgrade

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    struct TurretStats {
        int upgrade_cost,
            power,
            cost,
            fire_rate,
            radius,

            bullet_vx,
            bullet_vy,
            bullet_ax,
            bullet_ay;

        std::string name;
    };

    Turret(Tower *tower, sf::Texture *texture, int texture_index, const TurretStats& stats, TURRET_TYPE hashcode);
    Turret(Turret *turret);
    ~Turret();

    Turret *setUpgradeCost(int cost);
    Turret *setPower(int power);
    Turret *setCost(int cost);
    Turret *setFireRate(int fire_rate);
    Turret *setRadius(int radius);
    Turret *setTower(Tower *tower);
    Turret *setPosition(sf::Vector2f position);

    int getUpgradeCost();
    int getPower();
    int getFireRate();
    int getCost();
    int getLevel();
    int getRadius();
    int getBulletVX();
    int getBulletVY();
    int getBulletAX();
    int getBulletAY();
    TURRET_TYPE getHashCode();
    std::string getTurretName();
    Tower *getTower();
    sf::Sprite *getSprite();

    Turret *upgrade();
    Turret *shot();

    void registerEnemy(Enemy *enemy);
    void resetEnemy();
};


#endif //TD_TOWERDEFENSE_TURRET_H
