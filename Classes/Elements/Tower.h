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

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class Tower : public sf::Drawable, public sf::Transformable, public Notifier {
private:
    double max_hp,
        hp,
        gold;

    sf::RectangleShape rect,
        life_bar,
        death_bar;
    sptr<sf::Font> font;
    std::unordered_map<std::string, sptr<sf::Sprite>> sprites;
    sf::Text life,
        coin,

        wave,
        wave_2_boss,
        bosses,

        time;
    sf::Clock clock;
    
    DrawableFactory factory;

    unsigned long wave_time = 0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Tower(const sptr<sf::Font>& font, int life_point, double gold);

    void earn(int amount);
    bool pay(int amount);

    void setHp(int lp);
    void setGold(int amount);

    double getHp();
    double getGold();

    void damage(int damages);
    void syncStats();
};


#endif //TD_TOWERDEFENSE_TOWER_H
