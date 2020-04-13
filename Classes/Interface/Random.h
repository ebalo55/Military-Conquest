//
// Created by ebalo on 13/04/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RANDOM_H
#define TD_TOWERDEFENSE_SFML_RANDOM_H

#include <memory>
#include <random>

class Random {
private:
    std::shared_ptr<std::random_device> random_device;
    std::shared_ptr<std::default_random_engine> random_engine;
    std::uniform_int_distribution<> random;

public:
    Random() {
        random_device = std::make_shared<std::random_device>();
        random_engine = std::make_shared<std::default_random_engine>(std::default_random_engine((*random_device)()));
    }

    int generate_uniform(int min, int max) {
        random = std::uniform_int_distribution<>(min, max);
        return random(*random_engine);
    }

    static int generate(int min, int max) {
        std::random_device random_device;
        std::default_random_engine random_engine(random_device());

        std::uniform_int_distribution<> random(min, max);
        return random(random_engine);
    }
};

#endif //TD_TOWERDEFENSE_SFML_RANDOM_H
