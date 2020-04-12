//
// Created by michelangelo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_TURRET_H
#define TD_TOWERDEFENSE_TURRET_H

#include <cmath>
#include <forward_list>
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "../States/TurretState.h"
#include "Enemy.h"
#include "Bullet.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class Turret : public sf::Drawable, public sf::Transformable {
private:
    double upgrade_cost = 1,
        power = 1,
        cost = 1,
        fire_rate = 1,

        bullet_vx = 0,
        bullet_vy = 0;

    int level = 1,
        radius = 1;

    TURRET_TYPE hashcode;

    sptr<Tower> tower;
    std::string name;
    sptr<sf::Sprite> sprite;
    sptr<sf::Texture> texture;
    sf::Clock clock;

    DrawableFactory factory;

    sptr<std::forward_list<sptr<Bullet>>> bullets;
    std::vector<sptr<Bullet>> delete_queue;
    sptr<Enemy> victim = nullptr;

    double upgrade_factor_cost = 1.26,          // 26% upgrade
        upgrade_factor_power = 1.33,            // 33% upgrade
        upgrade_factor_fire_rate = 1.15;        // 15% upgrade

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct BulletComputedProps {
        double vx, vy;
    };

    BulletComputedProps computeBulletDirection(sf::Vector2f enemy_position);
    void shot(BulletComputedProps bullet_props);
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

    Turret(sptr<Tower> tower, const sptr<sf::Texture>& texture, int texture_index, const TurretStats& stats, TURRET_TYPE hashcode);
    Turret(const sptr<Turret>& turret);
    ~Turret();

    void setUpgradeCost(int cost);
    void setPower(int power);
    void setCost(int cost);
    void setFireRate(int fire_rate);
    void setRadius(int radius);
    void setTower(sptr<Tower> tower);
    void setPosition(sf::Vector2f position);

    int getUpgradeCost();
    int getPower();
    int getFireRate();
    int getCost();
    int getLevel();
    int getRadius();
    int getBulletVX();
    int getBulletVY();
    TURRET_TYPE getHashCode();
    std::string getTurretName();
    sptr<Tower> getTower();
    sptr<sf::Sprite> getSprite();
    sptr<sf::Texture> getTexture();
    sptr<std::forward_list<sptr<Bullet>>> getBulletsList();

    void upgrade();

    void registerEnemy(const sptr<Enemy>& enemy);
    void resetEnemy();
    void notify(sptr<Enemy> enemy);

    void registerBullet(const sptr<Bullet>& bullet);
    void deleteBullet(const sptr<Bullet>& bullet);
    void moveBullets(int elapsed_time, const sptr<std::forward_list<sptr<Enemy>>>& enemies);

    void markBulletAsDeleted(const sptr<Bullet>& bullet);
    void clearBulletsList();
};


#endif //TD_TOWERDEFENSE_TURRET_H
