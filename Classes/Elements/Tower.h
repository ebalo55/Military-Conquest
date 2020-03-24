//
// Created by ebalo on 23/03/20.
//

#ifndef TD_TOWERDEFENSE_TOWER_H
#define TD_TOWERDEFENSE_TOWER_H

#include <sstream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../Maps/AssetsMap.h"
#include "../States/windowSize.h"
#include "../Interface/Notifier.h"

class Tower : public sf::Drawable, public sf::Transformable, public Notifier {
private:
    double max_hp,
        hp,
        gold;

    sf::RectangleShape rect,
        life_bar,
        death_bar;
    sf::Font *font;
    std::unordered_map<std::string, sf::Sprite *> sprites;
    sf::Text life,
        coin,

        wave,
        wave_2_boss,
        bosses,

        time;
    sf::Clock clock;

    unsigned long wave_time = 0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Tower(sf::Font *font, int life_point, double gold, std::unordered_map<std::string, sf::Sprite *> sprites);

    Tower *earn(int amount);
    bool pay(int amount);

    Tower *setHp(int lp);
    Tower *setGold(int amount);

    double getHp();
    double getGold();

    Tower *damage(int damages);
    void syncStats();
};


#endif //TD_TOWERDEFENSE_TOWER_H
