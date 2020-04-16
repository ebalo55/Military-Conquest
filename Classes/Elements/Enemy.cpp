//
// Created by ebalo on 22/03/20.
//

#include "Enemy.h"

Enemy::Enemy(sptr<Map> map, bool is_map_easy, sptr<sf::Texture> texture, /*int texture_index,*/ EnemyStats stats/*, ENEMY_TYPE hashcode, bool animate_sprite, int animation_index, int animation_time*/) {
    this->map = map;
    map_width = map->getMapWidth();
    map_height = map->getMapHeight();
    this->is_map_easy = is_map_easy;
    if(!is_map_easy) {
        map_format = ((MapHard *)map.get())->getPath(Random::generate(0, ((MapHard *)map.get())->getPathsSize() -1));
    }
    else { map_format = map->getMap(); }
    type = stats.identifier;

    velocity = stats.velocity;
    acceleration = stats.acceleration;
    setVelocity(stats.velocity);
    setHP(stats.hp);
    setPower(stats.power);
    setAcceleration(stats.acceleration);
    setGenerationTime(stats.easy_gen_time, stats.hard_gen_time);

    texture_index = stats.tile_index;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(20 * texture_index, 0, 20, 20));
    if(stats.animated) {
        animate = true;
        animation_index = stats.animation_tile;
        animation_time = stats.animation_time;
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
Enemy::Enemy(const sptr<Enemy>& instance) {
    map = instance->map;
    map_width = map->getMapWidth();
    map_height = map->getMapHeight();
    is_map_easy = instance->isMapEasy();
    if(!instance->isMapEasy()) {
        map_format = ((MapHard *)map.get())->getPath(Random::generate(0, ((MapHard *)map.get())->getPathsSize() -1));
    }
    else { map_format = map->getMap(); }
    type = instance->getType();

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

    life_bar.setSize(sf::Vector2f {20, 2});
    life_bar.setOutlineColor(sf::Color(0x40, 0x99, 0x40));
    life_bar.setFillColor(sf::Color(0x40, 0x99, 0x40));
    life_bar.setPosition((float)enemy_size /2, (float)(40 * entrance +2));
    death_bar.setSize({0,5});
    death_bar.setFillColor(sf::Color {0x99, 0x40, 0x40});
    death_bar.setPosition((float)enemy_size /2 +20, (float)(40 * entrance +2));
}

void Enemy::setHP(double hp) {
    this->max_hp = this->hp = hp;
}

void Enemy::setPower(double power) {
    this->power = power;
}

void Enemy::setGenerationTime(double easy_time, double hard_time) {
    easy_gen_time = easy_time;
    hard_gen_time = hard_time;
}

double Enemy::getVelocity() { return velocity; }
double Enemy::getAcceleration() { return acceleration; }
double Enemy::getHP() { return hp; }
double Enemy::getPower() { return power; }
double Enemy::getGenerationTime(GAME_STATE difficult) { return difficult == GAME_STATE::game_difficulty_easy ? easy_gen_time : hard_gen_time; }
int Enemy::getType() { return type; }

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

    rotate();

    double offset_x = vx * time_lapse / 1000,
        offset_y = vy * time_lapse / 1000;
    sprite.move(offset_x, offset_y);
    life_bar.move(offset_x, offset_y);
    death_bar.move(offset_x, offset_y);

    animateSprite(time_lapse);
    notify();
}

void Enemy::hit(double damage) {
    hp -= damage;
    // 20 = length of bar
    double life_decrease_factor = hp / max_hp *20;
    life_bar.setSize({(float)(life_decrease_factor), 2});
    death_bar.setSize({(float)(20 - life_decrease_factor), 2});
    sf::Vector2f life_bar_position = life_bar.getPosition();
    death_bar.setPosition({(float)(life_bar_position.x + life_decrease_factor), life_bar_position.y});
    notify();
}

void Enemy::shot() {
    hp = 0;
    notify();
}

void Enemy::upgrade() {
    hp *= 1.25;
    power *= 1.25;
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

sf::FloatRect Enemy::getBoundingBox() {
    return sprite.getGlobalBounds();
}

void Enemy::animateSprite(int time_lapse) {
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
}

void Enemy::rotate() {
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
}
