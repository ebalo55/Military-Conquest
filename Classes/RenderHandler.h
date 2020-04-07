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
#include "Elements/EnemyGenerator.h"
#include "Elements/Tower.h"
#include "Elements/TurretGenerator.h"
#include "Elements/DrawableFactory.h"
#include "Elements/Bullet.h"

class RenderHandler : public DrawableFactory {
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Font> comfortaa;
    sf::Clock clock;

    std::shared_ptr<EventHandler> event_handler;
    std::vector<std::shared_ptr<Map>> maps;
    std::shared_ptr<GAME_STATE> state;

    std::unordered_map<std::string, bool> cleaning_state = {
            {"splash", true},
            {"difficult", true},
            {"game", true},
            {"game-over", true}
    };

    std::forward_list<Enemy *> enemies;
    EnemyGenerator *enemy_generator;

    TurretGenerator *turret_generator;

    Tower *tower;
    DrawableFactory factory;

    void initEnemyGenerator(sf::Texture *texture);
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

    void loopRender(const std::vector<sf::Drawable *>& container);
public:
    RenderHandler(std::shared_ptr<EventHandler> event_handler);
    ~RenderHandler();
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
