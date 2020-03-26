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
    upgrade_cost *= level % 10 == 0 ? 2 * upgrade_factor_cost : upgrade_factor_cost;
    power *= power < 10 && level % 5 == 0 ? 1.5 * upgrade_factor_power : upgrade_factor_power;
    fire_rate *= level % 5 == 0 ? 1.5 : 1;
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

Turret *Turret::shot(sf::Vector2f bullet_origin) {
    // TODO:
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