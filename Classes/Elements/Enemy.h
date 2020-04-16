//
// Created by ebalo on 22/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_ENEMY_H
#define TD_TOWERDEFENSE_SFML_ENEMY_H

#include <string>
#include <memory>
#include <forward_list>
#include "../Interface/Movement.h"
#include "../States/GameState.h"
#include "../Maps/Map.h"
#include "../Interface/Notifier.h"
#include "../Maps/MapHard.h"
#include "../States/windowSize.h"
#include "../States/EnemyState.h"
#include "../Interface/Random.h"
#include "../States/EnemyStats.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

enum Directions { unknown, left, right, top, bottom };

class Enemy : public sf::Drawable, public sf::Transformable, public Movement, public Notifier {
private:
    double hp = 1,
        power = 0,
        max_hp = 1,

        easy_gen_time,
        hard_gen_time,

        velocity = 0,
        acceleration = 0;

    const int enemy_size = 20;

    int type;
    int map_width,
        map_height,
        *map_format,

        texture_index,
        animation_index = 0,
        animation_time = 100,
        elapsed_time = 0;

    sf::RectangleShape life_bar,
        death_bar;

    bool is_map_easy = false,
        animate = false,
        second_frame = false,
        deleted = false;
    Directions last_direction = Directions::unknown;

    sf::Sprite sprite;
    sptr<Map> map;

    bool checkPath(int x_index, int y_index, int expected_code);
    void rotateEnemy(Directions direction);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();         // apply the transform
        target.draw(sprite, states);                 // draw the shape array
        target.draw(life_bar, states);
        target.draw(death_bar, states);
    }

    void animateSprite(int time_lapse);
    void rotate();
public:
    Enemy(sptr<Map> map, bool is_map_easy, sptr<sf::Texture> texture, EnemyStats stats);
    Enemy(const sptr<Enemy>& instance);

    void move(size_t time_lapse) override;

    void setHP(double hp);
    void setPower(double power);
    void setGenerationTime(double easy_time, double hard_time);
    void markAsDeleted();

    double getVelocity();
    double getAcceleration();
    double getHP();
    double getPower();
    double getGenerationTime(GAME_STATE difficult);
    const sf::Texture *getTexture();
    int getType();
    int getTextureIndex();
    bool isMapEasy();
    sf::Vector2f getPosition();
    bool getDeletedState();
    sf::FloatRect getBoundingBox();

    bool isAnimated();
    int getAnimationIndex();
    int getAnimationTime();

    void hit(double damage);
    void shot();
    void upgrade();
};


#endif //TD_TOWERDEFENSE_SFML_ENEMY_H
