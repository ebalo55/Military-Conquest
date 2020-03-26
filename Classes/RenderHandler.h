//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#define TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "Maps/Map.h"
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
#include "Elements/Turret.h"
#include "Elements/TurretGenerator.h"

class RenderHandler {
private:
    sf::RenderWindow *window;
    EventHandler *event_handler;

    std::vector<Map *> maps;
    GAME_STATE *state;

    std::unordered_map<std::string, sf::Texture> textures_map;
    std::unordered_map<std::string, sf::Sprite> sprites_map;
    std::unordered_map<std::string, ButtonRect> rect_buttons_map;
    std::unordered_map<std::string, sf::Text> texts_map;
    std::unordered_map<std::string, bool> cleaning_state = {
            {"splash", true},
            {"difficult", true},
            {"game-easy", true},
            {"game-hard", true},
            {"game-hacked", true},
            {"game-over", true}
    };
    sf::Font comfortaa;
    sf::Clock clock;

    std::forward_list<Enemy *> enemies;
    EnemyGenerator *enemy_generator;
    std::forward_list<Turret *> turrets;
    TurretGenerator *turret_generator;
    Tower *tower;

    void initEnemyGenerator(sf::Texture *texture);
    void initTower(int hp, double coin);

    sf::Sprite *initSprite(const std::string& name);
    sf::Sprite *getSprite(const std::string& name);
    sf::Texture *initTexture(const std::string& name);
    sf::Texture *getTexture(const std::string& name);
    ButtonRect *initButtonRect(const std::string& name);
    ButtonRect *getButtonRect(const std::string& name);
    sf::Text *initText(const std::string& name);
    sf::Text *getText(const std::string& name);

    void splashInit();
    void splashClear();
    void difficultInit();
    void difficultClear();
    void gameEasyInit();
    void gameEasyClear();
    void gameHardInit();
    void gameHardClear();
    void gameHackedInit();
    void gameHackedClear();
    void gameOverInit();
    void gameOverClear();

    void massClear(std::unordered_map<std::string, sf::Texture> *map, const std::vector<std::string>& names);
    void massClear(std::unordered_map<std::string, sf::Sprite> *map, const std::vector<std::string>& names);
    void massClear(std::unordered_map<std::string, ButtonRect> *map, const std::vector<std::string>& names);
    void massClear(std::unordered_map<std::string, sf::Text> *map, const std::vector<std::string>& names);

    void splashScreen();
    void difficultScreen();
    void gameEasyScreen();
    void gameHardScreen();
    void gameHackedScreen();
    void gameOverScreen();
public:
    RenderHandler(EventHandler *event_handler);
    ~RenderHandler();
    void handle();
};


#endif //TD_TOWERDEFENSE_SFML_RENDERHANDLER_H
