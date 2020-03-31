//
// Created by ebalo on 22/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_ENEMY_H
#define TD_TOWERDEFENSE_SFML_ENEMY_H

#include <string>
#include <random>
#include "../Interface/Movement.h"
//#include "../Elements/Tower.h"
#include "../States/GameState.h"
#include "../Maps/Map.h"
#include "../Interface/Notifier.h"
#include "../Maps/MapHard.h"
#include "../States/windowSize.h"

enum Directions { unknown, left, right, top, bottom };

class Enemy : public sf::Drawable, public sf::Transformable, public Movement, public Notifier {
private:
    double hp = 1,
        power = 0,
        shield = 0,

        easy_gen_time,
        hard_gen_time,

        velocity = 0,
        acceleration = 0;

    const int enemy_size = 20;
    int hash_code,

        map_width,
        map_height,
        *map_format,

        texture_index,
        animation_index = 0,
        animation_time = 100,
        elapsed_time = 0;

    bool is_map_easy = false,
        animate = false,
        second_frame = false;
    Directions last_direction = Directions::unknown;

    sf::Sprite sprite;
    Map *map;

    bool checkPath(int x_index, int y_index, int expected_code);
    void rotateEnemy(Directions direction);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();         // apply the transform
        target.draw(sprite, states);                 // draw the shape array
    }
public:
    struct Stats {
        double hp,
            velocity,
            acceleration,
            power,
            easy_gen_time,
            hard_gen_time;
    };

    Enemy(Map *map, bool is_map_easy, sf::Texture *texture, int texture_index, Enemy::Stats stats, int hashcode, bool animate_sprite = false, int animation_index = 0, int animation_time = 100);
    Enemy(Enemy *instance);

    void move(size_t time_lapse) override;

    Enemy *setHP(double hp);
    Enemy *setPower(double power);
    Enemy *setShield(double shield);
    Enemy *setGenerationTime(double easy_time, double hard_time);

    double getVelocity();
    double getAcceleration();
    double getHP();
    double getPower();
    double getShield();
    double getGenerationTime(GAME_STATE difficult);
    const sf::Texture *getTexture();
    int getHashCode();
    int getTextureIndex();
    bool isMapEasy();
    sf::Vector2f getPosition();

    bool isAnimated();
    int getAnimationIndex();
    int getAnimationTime();

    void hit(double damage);
    void shot();
    Enemy *upgrade();
};


#endif //TD_TOWERDEFENSE_SFML_ENEMY_H
