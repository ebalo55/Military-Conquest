//
// Created by ebalo on 13/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_WAVE_H
#define TD_TOWERDEFENSE_SFML_WAVE_H

#include <SFML/Graphics.hpp>

class Wave {
protected:
    sf::Clock clock;
    int time = 30;
    bool count_down = false;

    int wave_number = 0,
        boss_wave = 10;
public:
    Wave() {}
    virtual ~Wave() {}

    int getWaveNumber() {
        return wave_number;
    }
    int getWaveToBoss() {
        return wave_number % boss_wave;
    }
    int getWaitingTime() {
        return time - (int)clock.getElapsedTime().asSeconds();
    }
    bool isWaiting() {
        return count_down;
    }
    bool isBossWave() {
        return getWaveToBoss() == 0;
    }
};

#endif //TD_TOWERDEFENSE_SFML_WAVE_H
