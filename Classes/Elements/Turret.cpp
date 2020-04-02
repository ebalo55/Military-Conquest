// Created by michelangelo on 24/03/20.
//
#include "Turret.h"

#include <utility>

Turret::Turret(Tower *tower, sf::Texture *texture, int texture_index, const TurretStats& stats, TURRET_TYPE hashcode) {
    upgrade_cost = stats.upgrade_cost;
    power = stats.power;
    radius = stats.radius;
    fire_rate = stats.fire_rate;
    cost = stats.cost;

    bullet_vx = stats.bullet_vx;
    bullet_vy = stats.bullet_vy;
    bullet_ax = stats.bullet_ax;
    bullet_ay = stats.bullet_ay;
    name = stats.name;

    this->hashcode = hashcode;
    this->tower = tower;

    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect {40 * texture_index, 0, 40, 40});
}

Turret::Turret(Turret *turret) {
    upgrade_cost = turret->getUpgradeCost();
    power = turret->getPower();
    radius = turret->getRadius();
    fire_rate = turret->getFireRate();
    cost = turret->getCost();

    bullet_vx = turret->getBulletVX();
    bullet_vy = turret->getBulletVY();
    bullet_ax = turret->getBulletAX();
    bullet_ay = turret->getBulletAY();
    name = turret->getTurretName();

    hashcode = turret->getHashCode();
    tower = turret->getTower();

    sprite = *turret->getSprite();
}

Turret::~Turret() {

}

Turret *Turret::setUpgradeCost(int cost) {
    upgrade_cost = cost;
    return this;
}

Turret *Turret::setPower(int power) {
    this->power = power;
    return this;
}

Turret *Turret::setCost(int cost) {
    this->cost = cost;
    return this;
}

Turret *Turret::setFireRate(int fire_rate) {
    this->fire_rate = fire_rate;
    return this;
}

Turret *Turret::setRadius(int radius) {
    this->radius = radius;
    return this;
}

Turret *Turret::setTower(Tower *tower) {
    this->tower = tower;
    return this;
}

Turret *Turret::upgrade() {
    upgrade_cost *= upgrade_factor_cost;
    power *= upgrade_factor_power;
    fire_rate *= upgrade_factor_fire_rate;
    level++;
    return this;
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

Tower *Turret::getTower() {
    return tower;
}

Turret *Turret::shot() {
    /* TODO: This function should be called by an event or an observer on each enemy movement
     * Each turret has its own internal clock in order to let them shot independently
     */

    if(clock.getElapsedTime().asMilliseconds() >= 1000 / fire_rate) {
        // shot the bullet, where is the bullet ?!?!?!
        clock.restart();
    }
    return this;
}

int Turret::getBulletVX() {
    return bullet_vx;
}

int Turret::getBulletVY() {
    return bullet_vy;
}

int Turret::getBulletAX() {
    return bullet_ax;
}

int Turret::getBulletAY() {
    return bullet_ay;
}

TURRET_TYPE Turret::getHashCode() {
    return hashcode;
}

sf::Sprite *Turret::getSprite() {
    return &sprite;
}

std::string Turret::getTurretName() {
    return name;
}

void Turret::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();         // apply the transform
}

Turret *Turret::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
    return this;
}

void Turret::registerEnemy(Enemy *enemy) {
    /* TODO: An exception will be thrown as a died enemy instance is deleted but into the turret the pointer is not
     * TODO:    reset. A good way could be to broadcast an event to all the turrets to let them automatically reset their pointer if the
     * TODO:    instance of the enemy match the recorded instance. (pointer equality)
     */
    if(victim != nullptr) {
        sf::Vector2f victim_pos = victim->getPosition(),
                pos = sprite.getPosition();

        /* Check if the first enemy is currently into the range of the turret, if it is not the enemy instance is overwritten.
         * Note that as the turret radius is computed from the center an additional 20px are added to center the returned coordinates.
         */
        if(victim_pos.x < pos.x + 20 - radius || victim_pos.x > pos.x + 20 + radius || victim_pos.y < pos.y + 20 - radius || victim_pos.y > pos.y + 20 + radius) {
            victim = enemy;
        }
    }
    else { victim = enemy; }
}

void Turret::resetEnemy() {
    victim = nullptr;
}