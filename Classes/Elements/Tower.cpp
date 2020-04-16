//
// Created by ebalo on 23/03/20.
//

#include "Tower.h"

Tower::Tower(const sptr<sf::Font>& font, int life_point, double gold, sptr<Wave> wave_controller) :max_hp(life_point), hp(life_point), gold(gold), font(font),
        wave_controller(wave_controller) {
    factory.instantiateTexture("heart", AssetsMap::get("heart"));
    factory.instantiateTexture("coin", AssetsMap::get("coin"));
    factory.instantiateTexture("hud-bg", AssetsMap::get("hud-bg"));
    
    sprites = {
            {"heart",  std::make_shared<sf::Sprite>(*factory.instantiateSprite("heart", "heart"))},
            {"coin",   std::make_shared<sf::Sprite>(*factory.instantiateSprite("coin", "coin"))},
            {"hud-bg", std::make_shared<sf::Sprite>(*factory.instantiateSprite("hud-bg", "hud-bg"))}
    };
    
    sprites["hud-bg"]->setPosition(sf::Vector2f {WINDOW_WIDTH / 2, 0});

    sf::Color gray = sf::Color(0xcc, 0xcc, 0xcc);

    sprites["heart"]->setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 10, 10});
    life_bar.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 50, 15});
    life_bar.setFillColor(sf::Color(0x40, 0x99, 0x40));
    death_bar.setFillColor(sf::Color {0x99, 0x40, 0x40});
    life.setFont(*font);
    life.setFillColor(gray);
    life.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 560, 15});
    life.setCharacterSize(12);

    sprites["coin"]->setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 10, 40});
    coin.setFont(*font);
    coin.setFillColor(gray);
    coin.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 50, 40});
    coin.setCharacterSize(15);

    wave.setFont(*font);
    wave.setFillColor(gray);
    wave.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 115, 40});
    wave.setCharacterSize(15);
    new_wave_countdown.setFont(*font);
    new_wave_countdown.setFillColor(sf::Color(0xd4, 0xe7, 0x68));
    new_wave_countdown.setPosition(sf::Vector2f {WINDOW_WIDTH / 2 + 215, 40});
    new_wave_countdown.setCharacterSize(16);
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

void Tower::earn(int amount) {
    gold += amount;
}

bool Tower::pay(int amount) {
    if(gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Tower::setHp(int lp) {
    hp = lp;
}

void Tower::setGold(int amount) {
    gold = amount;
}

double Tower::getHp() { return hp; }

double Tower::getGold() { return gold; }

void Tower::damage(int damages) {
    hp -= damages;
    if(hp <= 0) {
        notify();
    }
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
    target.draw(new_wave_countdown, states);
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
    death_bar.setPosition(sf::Vector2f {(float)(WINDOW_WIDTH / 2 + 550 - lost_life_lenght), 15});
    life.setString(stringstream.str());

    stringstream.str("");
    stringstream << gold;

    coin.setString(stringstream.str());

    stringstream.str("");
    stringstream << "Wave: " << wave_controller->getWaveNumber();
    wave.setString(stringstream.str());
    if(wave_controller->isWaiting()) {
        stringstream.str("");
        stringstream << "New wave in " << wave_controller->getWaitingTime() << " sec/s";
        new_wave_countdown.setString(stringstream.str());
    }
    else { new_wave_countdown.setString(""); }

    if(wave_controller->isBossWave()) {
        bosses.setString("! BOSS !");
    }
    else {
        bosses.setString("");
    }

    stringstream.str("");
    int secs = clock.getElapsedTime().asSeconds();
    stringstream << secs / 600 << (secs / 60) % 10 << ":" << (secs / 10) % 6 << secs % 10;
    time.setString(stringstream.str());
}

void Tower::setWaveController(sptr<Wave> wave) {
    wave_controller = wave;
}
