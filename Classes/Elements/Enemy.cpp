//
// Created by ebalo on 22/03/20.
//

#include <iostream>
#include "Enemy.h"

Enemy::Enemy(Map *map, bool is_map_easy, sf::Texture *texture, int texture_index, Enemy::Stats stats, int hashcode, bool animate_sprite, int animation_index, int animation_time) {
    std::random_device random_device;
    std::default_random_engine random_engine(random_device());

    this->map = map;
    map_width = map->getMapWidth();
    map_height = map->getMapHeight();
    this->is_map_easy = is_map_easy;
    if(!is_map_easy) {
        std::uniform_int_distribution<> random(0, ((MapHard *)map)->getPathsSize() -1);
        map_format = ((MapHard *)map)->getPath(random(random_engine));
    }
    else { map_format = map->getMap(); }
    hash_code = hashcode;

    velocity = stats.velocity;
    acceleration = stats.acceleration;
    setVelocity(stats.velocity);
    setHP(stats.hp);
    setPower(stats.power);
    setAcceleration(stats.acceleration);
    setGenerationTime(stats.easy_gen_time, stats.hard_gen_time);

    this->texture_index = texture_index;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(20 * texture_index, 0, 20, 20));
    if(animate_sprite) {
        animate = true;
        this->animation_index = animation_index;
        this->animation_time = animation_time;
    }

    int entrance = 0;
    if(last_direction == Directions::unknown) {
        for(int i = 0; i < map_height; i++) {
            if(map_format[i * map_width] == 0) { entrance = i; break; }
        }

        sprite.setPosition(sf::Vector2f {(float)enemy_size, (float)(40 * entrance + enemy_size)});
        sprite.setOrigin(sf::Vector2f {sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2});
        last_direction = Directions::left;
        sprite.rotate(90);
    }
}
/**
 * Cloning constructor
 * @param Enemy1 *instance An already initialized instance of this class
 */
Enemy::Enemy(Enemy *instance) {
    map = instance->map;
    std::random_device random_device;
    std::default_random_engine random_engine(random_device());
    map_width = map->getMapWidth();
    map_height = map->getMapHeight();
    is_map_easy = instance->isMapEasy();
    if(!instance->isMapEasy()) {
        std::uniform_int_distribution<> random(0, ((MapHard *)map)->getPathsSize() -1);
        map_format = ((MapHard *)map)->getPath(random(random_engine));
    }
    else { map_format = map->getMap(); }
    hash_code = instance->hash_code;

    velocity = instance->getVelocity();
    acceleration = instance->getAcceleration();
    setVelocity(velocity);
    setHP(instance->getHP());
    setPower(instance->getPower());
    setAcceleration(acceleration);
    setGenerationTime(instance->getGenerationTime(GAME_STATE::game_difficulty_easy), instance->getGenerationTime(GAME_STATE::game_difficulty_hard));

    texture_index = instance->getTextureIndex();
    sprite.setTexture(*instance->getTexture());
    sprite.setTextureRect(sf::IntRect(20 * texture_index, 0, 20, 20));
    if(instance->isAnimated()) {
        animate = true;
        animation_index = instance->getAnimationIndex();
        animation_time = instance->getAnimationTime();
    }

    int entrance = 0;
    if(last_direction == Directions::unknown) {
        for(int i = 0; i < map_height; i++) {
            if(map_format[i * map_width] == 0) { entrance = i; break; }
        }

        sprite.setPosition(sf::Vector2f {(float)enemy_size, (float)(40 * entrance + enemy_size)});
        sprite.setOrigin(sf::Vector2f {sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2});
        last_direction = Directions::left;
        sprite.rotate(90);
    }
}

Enemy *Enemy::setHP(double hp) {
    this->hp = hp;
    return this;
}

Enemy *Enemy::setPower(double power) {
    this->power = power;
    return this;
}

Enemy *Enemy::setShield(double shield) {
    this->shield = shield;
    return this;
}

Enemy *Enemy::setGenerationTime(double easy_time, double hard_time) {
    easy_gen_time = easy_time;
    hard_gen_time = hard_time;
    return this;
}

double Enemy::getVelocity() { return velocity; }
double Enemy::getAcceleration() { return acceleration; }
double Enemy::getHP() { return hp; }
double Enemy::getPower() { return power; }
double Enemy::getShield() { return shield; }
double Enemy::getGenerationTime(GAME_STATE difficult) { return difficult == GAME_STATE::game_difficulty_easy ? easy_gen_time : hard_gen_time; }
int Enemy::getHashCode() { return hash_code; }

void Enemy::move(size_t time_lapse) {
    sf::Vector2f position = sprite.getPosition();
    if(position.x + enemy_size >= WINDOW_WIDTH) {
        shot();
        return;
    }

    int map_x_index = (position.x + (last_direction == Directions::left ? -enemy_size : last_direction == Directions::right ? enemy_size : 0)) / 40,
        map_y_index = (position.y + (last_direction == Directions::top ? -enemy_size : last_direction == Directions::bottom ? enemy_size : 0)) / 40,
        map_right_x_index = map_x_index +1 < map_width ? map_x_index +1 : map_x_index,
        map_left_x_index = map_x_index -1 > 0 ? map_x_index -1 : map_x_index,
        map_top_y_index = map_y_index -1 > 0 ? map_y_index -1 : map_y_index,
        map_bottom_y_index = map_y_index +1 < map_height ? map_y_index +1 : map_y_index;

    vx = vy = 0;

    if(checkPath(map_right_x_index, map_y_index, 0) && last_direction != Directions::right) { vx = velocity; }
    if(checkPath(map_left_x_index, map_y_index, 0) && last_direction != Directions::left) { vx = -velocity; }
    if(checkPath(map_x_index, map_top_y_index, 0) && last_direction != Directions::top) { vy = -velocity; }
    if(checkPath(map_x_index, map_bottom_y_index, 0) && last_direction != Directions::bottom) { vy = velocity; }


    // Remember: last_direction contains the direction from where the enemy is coming NOT the current direction
    if(vx != 0 && vy != 0) {
        if((last_direction == Directions::left && vx > 0) || (last_direction == Directions::right && vx < 0)) { vy = 0; }
        else if((last_direction == Directions::bottom && vy < 0) || (last_direction == Directions::top && vy > 0)) { vx = 0; }
    }

    if(vx > 0) {
        rotateEnemy(Directions::left);
        last_direction = Directions::left;
    }
    else if(vx < 0) {
        rotateEnemy(Directions::right);
        last_direction = Directions::right;
    }
    else if(vy < 0) {
        rotateEnemy(Directions::bottom);
        last_direction = Directions::bottom;
    }
    else {
        rotateEnemy(Directions::top);
        last_direction = Directions::top;
    }

    sprite.move(vx * time_lapse / 1000, vy * time_lapse / 1000);
    if(animate) {
        elapsed_time += time_lapse;
        if (elapsed_time >= animation_time) {
            if (!second_frame) {
                sprite.setTextureRect(sf::IntRect{20 * animation_index, 0, 20, 20});
                second_frame = true;
            }
            else {
                sprite.setTextureRect(sf::IntRect{20 * texture_index, 0, 20, 20});
                second_frame = false;
            }
            elapsed_time = 0;
        }
    }
    notify();
}

void Enemy::hit(double damage) {
    hp -= damage;
    notify();
}

void Enemy::shot() {
    hp = 0;
    notify();
}

Enemy *Enemy::upgrade() {
    hp += hp * .25;
    power += power * .25;
    return nullptr;
}

const sf::Texture *Enemy::getTexture() {
    return sprite.getTexture();
}

void Enemy::rotateEnemy(Directions direction) {
    switch(last_direction) {
        case left:
            sprite.rotate(direction == Directions::top ? 90 : direction == Directions::right ? 180 : direction == Directions::bottom ? 270 : 0);
            break;
        case right:
            sprite.rotate(direction == Directions::top ? 270 : direction == Directions::bottom ? 90 : direction == Directions::left ? 180 : 0);
            break;
        case top:
            sprite.rotate(direction == Directions::right ? 90 : direction == Directions::bottom ? 180 : direction == Directions::left ? 270 : 0);
            break;
        case bottom:
            sprite.rotate(direction == Directions::top ? 180 : direction == Directions::right ? 270 : direction == Directions::left ? 90 : 0);
            break;
    }
}

bool Enemy::checkPath(int x_index, int y_index, int expected_code) {
    return map_format[x_index + y_index * map_width] == expected_code;
}

bool Enemy::isMapEasy() {
    return is_map_easy;
}

int Enemy::getTextureIndex() {
    return texture_index;
}

bool Enemy::isAnimated() {
    return animate;
}

int Enemy::getAnimationIndex() {
    return animation_index;
}

int Enemy::getAnimationTime() {
    return animation_time;
}

sf::Vector2f Enemy::getPosition() {
    return sprite.getPosition();
}

void Enemy::markAsDeleted() {
    deleted = true;
}

bool Enemy::getDeletedState() {
    return deleted;
}
