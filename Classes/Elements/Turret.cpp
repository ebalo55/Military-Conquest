// Created by michelangelo on 24/03/20.
//
#include "Turret.h"

#include <cmath>
#include <utility>

Turret::Turret(sptr<Tower> tower, const sptr<sf::Texture>& texture, const TurretStats &stats) {
    upgrade_cost = stats.upgrade_cost;
    power = stats.power;
    radius = stats.radius;
    fire_rate = stats.fire_rate;
    cost = stats.cost;
    this->texture = texture;

    name = stats.name;

    type = stats.identifier;
    this->tower = tower;

    bullets = std::make_shared<std::forward_list<sptr<Bullet>>>(std::forward_list<sptr<Bullet>>());

    sprite = factory.instantiateSprite("turret-sprite", texture, {0,0},sf::IntRect{40 * stats.tile_index, 0, 40, 40});
}

Turret::Turret(const sptr<Turret>& turret) {
    upgrade_cost = turret->getUpgradeCost();
    power = turret->getPower();
    radius = turret->getRadius();
    fire_rate = turret->getFireRate();
    cost = turret->getCost();

    name = turret->getTurretName();

    type = turret->getType();
    tower = turret->getTower();

    bullets = turret->getBulletsList();
    sprite = turret->getSprite();
}

Turret::~Turret() {

}

void Turret::setUpgradeCost(int cost) {
    upgrade_cost = cost;
}

void Turret::setPower(int power) {
    this->power = power;
}

void Turret::setCost(int cost) {
    this->cost = cost;
}

void Turret::setFireRate(int fire_rate) {
    this->fire_rate = fire_rate;
}

void Turret::setRadius(int radius) {
    this->radius = radius;
}

void Turret::setTower(sptr<Tower> tower) {
    this->tower = tower;
}

void Turret::upgrade() {
    upgrade_cost *= upgrade_factor_cost;
    power *= upgrade_factor_power;
    fire_rate *= upgrade_factor_fire_rate;
    level++;
}

int Turret::getUpgradeCost() {
    return upgrade_cost;
}

int Turret::getPower() {
    return power;
}

int Turret::getFireRate() {
    return fire_rate;
}

int Turret::getCost() {
    return cost;
}

int Turret::getLevel() {
    return level;
}

int Turret::getRadius() {
    return radius;
}

sptr<Tower> Turret::getTower() {
    return tower;
}

void Turret::shot(BulletComputedProps bullet_props) {
    // Each turret has its own internal clock in order to let them shot independently

    if (victim != nullptr && clock.getElapsedTime().asMilliseconds() >= 1000 / fire_rate) {
        bullets->push_front(std::make_shared<Bullet>(Bullet(bullet_props.vx, bullet_props.vy, power, turret_position_on_map)));
        clock.restart();
    }
}

int Turret::getType() {
    return type;
}

sptr<sf::Sprite> Turret::getSprite() {
    return sprite;
}

std::string Turret::getTurretName() {
    return name;
}

void Turret::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();         // apply the transform
}

void Turret::setPosition(sf::Vector2f position) {
    turret_position_on_map = position;
}

void Turret::registerEnemy(sptr<Enemy>& enemy) {
    sf::Vector2f victim_pos {-1, -1},
        enemy_pos = enemy->getPosition();
    int hp = 1;
    if(victim != nullptr) {
        victim_pos = victim->getPosition();
        hp = victim->getHP();
    }

    // Refresh the current instance of victim in order to refresh the position
    if(victim.get() == enemy.get()) {
        victim = enemy;
        victim_pos = victim->getPosition();
    }

    // Check if the first enemy is currently into the range of the turret, if it is not the enemy instance is nulled.
    if(hp <= 0 || (victim_pos.x < turret_position_on_map.x - radius || victim_pos.x > turret_position_on_map.x + radius) ||
            (victim_pos.y < turret_position_on_map.y - radius || victim_pos.y > turret_position_on_map.y + radius)) {
        victim = nullptr;
    }

    // Check whether the referenced enemy is into the radius of the turret in the case it is, it will be the current victim
    if((hp <= 0 || victim == nullptr) && (enemy_pos.x > turret_position_on_map.x - radius && enemy_pos.x < turret_position_on_map.x + radius) &&
       (enemy_pos.y > turret_position_on_map.y - radius && enemy_pos.y < turret_position_on_map.y + radius)) {
        victim = enemy;
    }
}

void Turret::resetEnemy() {
    victim = nullptr;
}

sptr<sf::Texture> Turret::getTexture() {
    return texture;
}

Turret::BulletComputedProps Turret::computeBulletDirection(sf::Vector2f enemy_position, int elapsed_time) {
    double x_diff = enemy_position.x - turret_position_on_map.x,
        y_diff = enemy_position.y - turret_position_on_map.y;

    return Turret::BulletComputedProps {x_diff / elapsed_time *100, y_diff / elapsed_time *100};
}

void Turret::notify(sptr<Enemy>& enemy, int elapsed_time) {
    registerEnemy(enemy);
    if(victim != nullptr) {
        shot(computeBulletDirection(victim->getPosition(), elapsed_time));
    }
}

sptr<std::forward_list<sptr<Bullet>>> Turret::getBulletsList() {
    return bullets;
}

void Turret::registerBullet(const sptr<Bullet> &bullet) {
    bullets->push_front(bullet);
}

void Turret::deleteBullet(const sptr<Bullet> &bullet) {
    bullets->remove(bullet);
}

void Turret::moveBullets(int elapsed_time, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies) {
    for(const sptr<Bullet>& bullet : *bullets) {
        bullet->move(elapsed_time);
        if(bullet->checkCollision(enemies) || bullet->isOutOfMap()) {
            markBulletAsDeleted(bullet);
        }
    }
    clearBulletsList();
}

void Turret::markBulletAsDeleted(const sptr<Bullet>& bullet) {
    delete_queue.push_back(bullet);
}

void Turret::clearBulletsList() {
    for(const sptr<Bullet>& bullet : delete_queue) {
        bullets->remove(bullet);
    }
    delete_queue.clear();
}
