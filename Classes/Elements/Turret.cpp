// Created by michelangelo on 24/03/20.
//
#include "Turret.h"

#include <cmath>
#include <utility>

Turret::Turret(sptr<Tower> tower, const sptr<sf::Texture>& texture, int texture_index, const TurretStats &stats, TURRET_TYPE hashcode) {
    upgrade_cost = stats.upgrade_cost;
    power = stats.power;
    radius = stats.radius;
    fire_rate = stats.fire_rate;
    cost = stats.cost;
    this->texture = texture;

    name = stats.name;

    this->hashcode = hashcode;
    this->tower = tower;

    bullets = std::make_shared<std::forward_list<sptr<Bullet>>>(std::forward_list<sptr<Bullet>>());

    sprite = factory.instantiateSprite("turret-sprite", texture, {0,0},sf::IntRect{40 * texture_index, 0, 40, 40});
}

Turret::Turret(const sptr<Turret>& turret) {
    upgrade_cost = turret->getUpgradeCost();
    power = turret->getPower();
    radius = turret->getRadius();
    fire_rate = turret->getFireRate();
    cost = turret->getCost();

    name = turret->getTurretName();

    hashcode = turret->getHashCode();
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
    /* TODO: This function should be called by an event or an observer on each enemy movement
     * Each turret has its own internal clock in order to let them shot independently
     */

    if (victim != nullptr && clock.getElapsedTime().asMilliseconds() >= 1000 / fire_rate) {
        bullets->push_front(std::make_shared<Bullet>(Bullet(bullet_props.vx, bullet_props.vy, power, turret_position_on_map)));
        clock.restart();
    }
}

TURRET_TYPE Turret::getHashCode() {
    return hashcode;
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

void Turret::registerEnemy(const sptr<Enemy>& enemy) {
    sf::Vector2f victim_pos {-1, -1},
        enemy_pos = enemy->getPosition();
    if(victim != nullptr) {
        victim_pos = victim->getPosition();
    }

    /* Check if the first enemy is currently into the range of the turret, if it is not the enemy instance is nulled.
     * Note that as the turret radius is computed from the center an additional 20px are added to center the returned coordinates.
     */
    if((victim_pos.x < turret_position_on_map.x - radius || victim_pos.x > turret_position_on_map.x + radius) ||
            (victim_pos.y < turret_position_on_map.y - radius || victim_pos.y > turret_position_on_map.y + radius)) {
        victim = nullptr;
    }

    std::cout << getTurretName() << "\n\tvictim-x: " << victim_pos.x << "\n\tturret-limit-left: " << turret_position_on_map.x - radius <<
        "\n\tturret-limit-right: " << turret_position_on_map.x + radius << "\n\n\tvictim-y: " << victim_pos.y <<
        "\n\tturret-top-limit: " << turret_position_on_map.y - radius << "\n\tturret-bottom-limit: " << turret_position_on_map.y + radius << "\n\n\tvictim: " << victim << "\n\n";

    // Check whether the referenced enemy is into the radius of the turret in the case it is, it will be the current victim
    if(victim == nullptr && (enemy_pos.x > turret_position_on_map.x - radius && enemy_pos.x < turret_position_on_map.x + radius) &&
       (enemy_pos.y > turret_position_on_map.y - radius && enemy_pos.y < turret_position_on_map.y + radius)) {
        victim = enemy;
    }

    std::cout << "\tenemy-x: " << enemy_pos.x  << "\n\tenemy-y: " << enemy_pos.y << "\n\tvictim: " << victim << "\n\tenemy: " << enemy << "\n---------------------------------------------------------\n";
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

void Turret::notify(const sptr<Enemy>& enemy, int elapsed_time) {
    registerEnemy(enemy);
    shot(computeBulletDirection(enemy->getPosition(), elapsed_time));
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
