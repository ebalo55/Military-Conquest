//
// Created by ebalo on 23/03/20.
//

#ifndef TD_TOWERDEFENSE_TOWER_H
#define TD_TOWERDEFENSE_TOWER_H

#include <memory>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../Maps/AssetsMap.h"
#include "../States/windowSize.h"
#include "../Interface/Notifier.h"
#include "DrawableFactory.h"
#include "../Interface/Wave.h"
#include "../Parser/Config.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class Tower : public sf::Drawable, public sf::Transformable, public Notifier {
private:
    double max_hp,
        hp,
        gold;

    sf::RectangleShape life_bar,
        death_bar;
    sptr<sf::Font> font;
    std::unordered_map<std::string, sptr<sf::Sprite>> sprites;
    sf::Text life,
        coin,

        wave,
        new_wave_countdown,
        bosses,

        time;
    sf::Clock clock;
    
    DrawableFactory factory;

    sptr<Wave> wave_controller;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Tower(const sptr<sf::Font>& font, int life_point, double gold, sptr<Wave> wave);

    void earn(int amount);
    bool pay(int amount);

    void setHp(int lp);
    void setGold(int amount);
    void setWaveController(sptr<Wave> wave);

    double getHp();
    double getGold();

    void damage(int damages);
    void syncStats();
};


#endif //TD_TOWERDEFENSE_TOWER_H
