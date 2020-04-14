//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#define TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <memory>
#include "Maps/MapEasy.h"
#include "Maps/MapHard.h"
#include "States/GameState.h"
#include "Elements/ButtonRect.h"
#include "EventHandler.h"
#include "Elements/Enemy.h"
#include "States/windowSize.h"
#include "States/EnemyState.h"
#include "Events/StartButtonHover.h"
#include "Observers/MouseHoverObserver.h"
#include "Observers/MouseOutObserver.h"
#include "Observers/MouseClickObserver.h"
#include "Events/StartButtonClick.h"
#include "Events/DifficultButtonHover.h"
#include "Events/DifficultEasyButtonClick.h"
#include "Elements/Tower.h"
#include "Elements/TurretGenerator.h"
#include "Elements/DrawableFactory.h"
#include "Elements/Bullet.h"
#include "Elements/WaveController.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class RenderHandler : public DrawableFactory {
private:
    sptr<sf::RenderWindow> window;
    sptr<sf::Font> comfortaa;
    sf::Clock clock;

    sptr<EventHandler> event_handler;
    std::vector<sptr<Map>> maps;
    sptr<GAME_STATE> state;

    std::unordered_map<std::string, bool> cleaning_state = {
            {"splash", true},
            {"difficult", true},
            {"game", true},
            {"game-over", true}
    };

    sptr<std::map<unsigned long long, sptr<Enemy>>> enemies;
    std::vector<sptr<Enemy>> to_remove;
    sptr<WaveController> wave_controller;

    TurretGenerator *turret_generator;

    sptr<Tower> tower;
    DrawableFactory factory;

    void initEnemyGenerator();
    void initTower(int hp, double coin);

    void splashInit();
    void splashClear();
    void difficultInit();
    void difficultClear();
    void gameInit();
    void gameClear();
    void gameOverInit();
    void gameOverClear();

    void splashScreen();
    void difficultScreen();
    void gameScreen();
    void gameOverScreen();

    void loopRender(const std::vector<sptr<sf::Drawable>>& container);
    void loopRemove();
public:
    RenderHandler(const sptr<EventHandler>& event_handler);
    ~RenderHandler();
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
