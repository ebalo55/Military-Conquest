//
// Created by ebalo on 23/03/20.
//

#include "Tower.h"

Tower::Tower(sf::Font *font, int life_point, double gold, std::unordered_map<std::string, sf::Sprite *> sprites) :max_hp(life_point), hp(life_point), gold(gold), font(font), sprites(std::move(sprites)) {
    sf::Sprite *sprite = this->sprites["hud-bg"];
    sprite->setPosition(sf::Vector2f {WINDOW_WIDTH / 2, 0});

    sf::Color gray = sf::Color(0xcc, 0xcc, 0xcc);

    sprite = this->sprites["heart"];
    sprite->setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 10, 10});
    life_bar.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 50, 15});
    life_bar.setFillColor(sf::Color(0x40, 0x99, 0x40));
    death_bar.setFillColor(sf::Color {0x99, 0x40, 0x40});
    life.setFont(*font);
    life.setFillColor(gray);
    life.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 560, 15});
    life.setCharacterSize(12);

    sprite = this->sprites["coin"];
    sprite->setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 10, 40});
    coin.setFont(*font);
    coin.setFillColor(gray);
    coin.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 50, 40});
    coin.setCharacterSize(15);

    wave.setFont(*font);
    wave.setFillColor(gray);
    wave.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 115, 40});
    wave.setCharacterSize(15);
    wave_2_boss.setFont(*font);
    wave_2_boss.setFillColor(gray);
    wave_2_boss.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 215, 40});
    wave_2_boss.setCharacterSize(15);
    bosses.setFont(*font);
    bosses.setFillColor(sf::Color(0xff, 0x55, 0x55));
    bosses.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 550, 40});
    bosses.setStyle(sf::Text::Style::Bold);
    bosses.setCharacterSize(15);

    time.setFont(*font);
    time.setFillColor(gray);
    time.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 425, 40});
    time.setCharacterSize(15);
}

Tower *Tower::earn(int amount) {
    gold += amount;
    return this;
}

bool Tower::pay(int amount) {
    if(gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

Tower *Tower::setHp(int lp) {
    hp = lp;
    return this;
}

Tower *Tower::setGold(int amount) {
    gold = amount;
    return this;
}

double Tower::getHp() { return hp; }

double Tower::getGold() { return gold; }

Tower *Tower::damage(int damages) {
    hp -= damages;
    if(hp <= 0) {
        notify();
    }
    return this;
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();         // apply the transform

    target.draw(*(sprites.at("hud-bg")), states);
    target.draw(*(sprites.at("heart")), states);
    target.draw(life_bar, states);
    target.draw(death_bar, states);
    target.draw(life, states);
    target.draw(*(sprites.at("coin")), states);
    target.draw(coin, states);
    target.draw(wave, states);
    target.draw(wave_2_boss, states);
    target.draw(bosses, states);
    target.draw(time, states);
}

void Tower::syncStats() {
    std::stringstream stringstream;
    stringstream << hp << " / " << max_hp;

    int lifebar_lenght = 500 * hp / max_hp,
            lost_life_lenght = 500 - lifebar_lenght;

    life_bar.setSize(sf::Vector2f {(float)lifebar_lenght, 10});
    death_bar.setSize(sf::Vector2f {(float)lost_life_lenght, 10});
    death_bar.setPosition(sf::Vector2f {(float)(WINDOW_WIDTH / 2 + 550 - lost_life_lenght), 10});
    life.setString(stringstream.str());

    stringstream.str("");
    stringstream << gold;

    coin.setString(stringstream.str());

    wave.setString("Wave: 10");
    wave_2_boss.setString("Boss in 0 waves");
    bosses.setString("! Boss !");

    stringstream.str("");
    int secs = clock.getElapsedTime().asSeconds();
    stringstream << secs / 600 << (secs / 60) % 10 << ":" << (secs / 10) % 6 << secs % 10;
    time.setString(stringstream.str());
}
