//
// Created by ebalo on 20/03/20.
//

#include "RenderHandler.h"
#include "Observers/TowerLPObserver.h"

RenderHandler::RenderHandler(EventHandler *event_handler) {
    this->event_handler = event_handler;

    // Global initialization
    window = event_handler->getRenderWindow();
    state = event_handler->getGameState();
    comfortaa.loadFromFile(AssetsMap::get("font-comfortaa"));
    maps = {new MapEasy(), new MapHard()};
    factory.setEventHandler(event_handler);
    factory.setWindow(window);
}

RenderHandler::~RenderHandler() {
    for(int i = 0; i < maps.size(); i++) { delete maps[i]; }
}

void RenderHandler::handle() {
    window->clear(sf::Color(0x75, 0x8d, 0x1f));            // Clear the window
    switch(*state) {
        case initial_screen:
            if(cleaning_state["splash"]) { splashInit(); }
            splashScreen();
            break;
        case difficulty_screen:
            if(cleaning_state["difficult"]) { difficultInit(); }
            if(!cleaning_state["splash"]) { splashClear(); }
            if(!cleaning_state["game-over"]) { gameOverClear(); }
            difficultScreen();
            break;
        case game_difficulty_easy:
            if(cleaning_state["game-easy"]) { gameEasyInit(); }
            if(!cleaning_state["difficult"]) { difficultClear(); }
            gameEasyScreen();
            break;
        case game_difficulty_hard:
            if(cleaning_state["game-hard"]) { gameHardInit(); }
            if(!cleaning_state["difficult"]) { difficultClear(); }
            gameHardScreen();
            break;
        case game_difficulty_hacked:
            if(cleaning_state["game-hacked"]) { gameHackedInit(); }
            if(!cleaning_state["difficult"]) { difficultClear(); }
            gameHackedScreen();
            break;
        case game_over:
            if(cleaning_state["game-over"]) { gameOverInit(); }
            if(!cleaning_state["game-easy"]) { gameEasyClear(); }
            if(!cleaning_state["game-hard"]) { gameHardClear(); }
            if(!cleaning_state["game-hacked"]) { gameHackedClear(); }
            gameOverScreen();
            break;
    }
    window->display();          // End frame and display content
}

void RenderHandler::splashScreen() {
    loopRender({
        maps[1],
        factory.getSprite("logo"),
        factory.getButtonRect("start")
    });
}

void RenderHandler::difficultScreen() {
    loopRender({
        maps[1],
        factory.getSprite("rounded-box"),
        factory.getText("title"),
        factory.getText("difficult-easy"),
        factory.getText("difficult-hard"),
        factory.getText("difficult-hacked"),
        factory.getButtonRect("difficult-easy"),
        factory.getButtonRect("difficult-hard"),
        factory.getButtonRect("difficult-hacked")
    });
}

void RenderHandler::gameEasyScreen() {
    window->draw(*(maps[0]));
    int elapsed_time = clock.restart().asMilliseconds();
    enemy_generator->tick(elapsed_time);
    for(Enemy *enemy : enemies) {
        enemy->move(elapsed_time);
        window->draw(*enemy);
    }
    tower->syncStats();
    window->draw(*tower);
    window->draw(*turret_generator);
    enemy_generator->syncEnemies();
}

void RenderHandler::gameHardScreen() {
    window->draw(*(maps[1]));
    int elapsed_time = clock.restart().asMilliseconds();
    enemy_generator->tick(elapsed_time);
    for(Enemy *enemy : enemies) {
        enemy->move(elapsed_time);
        window->draw(*enemy);
    }
    enemy_generator->syncEnemies();
}

void RenderHandler::gameHackedScreen() {
    window->draw(*(maps[1]));
    int elapsed_time = clock.restart().asMilliseconds();
    enemy_generator->tick(elapsed_time);
    for(Enemy *enemy : enemies) {
        enemy->move(elapsed_time);
        window->draw(*enemy);
    }
    enemy_generator->syncEnemies();
}

void RenderHandler::gameOverScreen() {
    window->draw(*(maps[1]));
}

void RenderHandler::splashInit() {
    factory.instantiateTexture("logo", AssetsMap::get("logo"));

    sf::Sprite *sprite = factory.instantiateSprite("logo", "logo");
    sprite->setPosition((WINDOW_WIDTH - sprite->getLocalBounds().width) / 2, (WINDOW_HEIGHT - sprite->getLocalBounds().height) / 2);

    ButtonRect *start = factory.instantiateButtonRect("start",
            sf::Vector2i {75, 40},
            &comfortaa,
            "Start",
            18,
            sf::Color(0, 0, 0),
            sf::Color(0, 0, 0),
            sf::Vector2f {(WINDOW_WIDTH - 75) / 2, WINDOW_HEIGHT - 100});
    factory.linkEvent(start,
            new StartButtonHoverEvent(start, false),
            new StartButtonHoverEvent(start),
            new StartButtonClickEvent(start, state));

    cleaning_state["splash"] = false;
}

void RenderHandler::splashClear() {
    factory.clear(DrawableFactory::Maps::textures, {"logo"});
    factory.clear(DrawableFactory::Maps::sprites, {"logo"});
    factory.unlinkButton("start");
    factory.clear(DrawableFactory::Maps::rect_buttons, {"start"});

    cleaning_state["splash"] = true;
}

void RenderHandler::difficultInit() {
    factory.instantiateTexture("rounded-box", AssetsMap::get("rounded-box"));

    sf::Sprite *sprite = factory.instantiateSprite("rounded-box", "rounded-box");
    sprite->setPosition((WINDOW_WIDTH - sprite->getLocalBounds().width) / 2, (WINDOW_HEIGHT - sprite->getLocalBounds().height) / 2);

    sf::Text *text = factory.instantiateText("title",
            &comfortaa,
            "Choose a difficulty to start playing the game",
            sf::Vector2f {0, 0},
            35,
            sf::Color(0, 0, 0),
            sf::Text::Style::Bold);
    text->setPosition(sf::Vector2f {sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width - text->getLocalBounds().width) / 2, sprite->getGlobalBounds().top + 25});

    factory.instantiateText("difficult-easy",
            &comfortaa,
            "One path only, standard enemies and\n  resources, bosses every 10 waves.",
            sf::Vector2f {sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 150},
            26);
    factory.instantiateText("difficult-hard",
            &comfortaa,
            "Multiple paths, stronger enemies and\n  less resources,bosses every 5 waves.",
            sf::Vector2f {sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 300},
            26);
    factory.instantiateText("difficult-hacked",
            &comfortaa,
            "Multiple paths, stronger enemies and\n  unlimited resources, bosses every 5 waves.",
            sf::Vector2f {sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 450},
            26);

    ButtonRect *btn = factory.instantiateButtonRect("difficult-easy",
            sf::Vector2i {75, 40},
            &comfortaa,
            "Easy",
            18,
            sf::Color(0x3f, 0xb9, 0x1f),
            sf::Color(0x49, 0xd1, 0x41),
            sf::Vector2f {sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125, sprite->getGlobalBounds().top + 160});
    factory.linkEvent(btn,
            new DifficultButtonHoverEvent(btn, false, sf::Color(0x49, 0xd1, 0x41)),
            new DifficultButtonHoverEvent(btn, true, sf::Color(0xee, 0xee, 0xee)),
            new DifficultButtonClickEvent(btn, state, GAME_STATE::game_difficulty_easy));

    btn = factory.instantiateButtonRect("difficult-hard",
            sf::Vector2i {75, 40},
            &comfortaa,
            "Hard",
            18,
            sf::Color(0xcc, 0x30, 0x10),
            sf::Color(0xee, 0x50, 0x30),
            sf::Vector2f {sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125, sprite->getGlobalBounds().top + 310});
    factory.linkEvent(btn,
            new DifficultButtonHoverEvent(btn, false, sf::Color(0xee, 0x50, 0x30)),
            new DifficultButtonHoverEvent(btn, true, sf::Color(0xee, 0xee, 0xee)),
            new DifficultButtonClickEvent(btn, state, GAME_STATE::game_difficulty_hard));

    btn = factory.instantiateButtonRect("difficult-hacked",
            sf::Vector2i {75, 40},
            &comfortaa,
            "Hacked",
            18,
            sf::Color(0xcc, 0xcc, 0x30),
            sf::Color(0x99, 0x99, 0x30),
            sf::Vector2f {sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125, sprite->getGlobalBounds().top + 460});
    factory.linkEvent(btn,
            new DifficultButtonHoverEvent(btn, false, sf::Color(0x99, 0x99, 0x30)),
            new DifficultButtonHoverEvent(btn, true, sf::Color(0x20, 0x20, 0x20)),
            new DifficultButtonClickEvent(btn, state, GAME_STATE::game_difficulty_hacked));

    cleaning_state["difficult"] = false;
}

void RenderHandler::difficultClear() {
    factory.clear(DrawableFactory::Maps::textures, {"rounded-box"});
    factory.clear(DrawableFactory::Maps::sprites, {"rounded-box"});
    factory.clear(DrawableFactory::Maps::texts, {"title", "difficult-easy", "difficult-hard", "difficult-hacked"});
    factory.unlinkButton({"difficult-easy", "difficult-hard", "difficult-hacked"});
    factory.clear(DrawableFactory::Maps::rect_buttons, {"difficult-easy", "difficult-hard", "difficult-hacked"});

    cleaning_state["difficult"] = true;
}

void RenderHandler::gameEasyInit() {
    initTower(1000, 100);

    sf::Texture *texture = factory.instantiateTexture("enemies", AssetsMap::get("enemies-tile-set"));
    initEnemyGenerator(texture);
    //enemy_generator->genFixedNumber(ENEMY_TYPE::boss3, 100);

    texture = factory.instantiateTexture("turret-tile", AssetsMap::get("tile-set"));
    turret_generator = new TurretGenerator(window, &comfortaa, event_handler, maps[0], {
        new Turret(tower, texture, 5, Turret::TurretStats {8,3,10,3,80,200,200,0,0,"Turret 1"},
                TURRET_TYPE::turret1),
        new Turret(tower, texture, 6, Turret::TurretStats {10,5,13,2,60,200,200,0,0,"Turret 2"},
                   TURRET_TYPE::turret2),
        new Turret(tower, texture, 7, Turret::TurretStats {15,5,20,5,100,200,200,0,0,"Turret 3"},
                   TURRET_TYPE::turret3),
        new Turret(tower, texture, 8, Turret::TurretStats {5,2,7,2,80,200,200,0,0,"Turret 4"},
                   TURRET_TYPE::turret4),
        new Turret(tower, texture, 9, Turret::TurretStats {13,3,15,5,120,200,200,0,0,"Turret 5"},
                   TURRET_TYPE::turret5),
    });

    clock.restart();
    cleaning_state["game-easy"] = false;
}

void RenderHandler::gameEasyClear() {
    delete enemy_generator;
    delete tower;
    factory.clear(DrawableFactory::Maps::textures, {"enemies", "turret-tile"});

    cleaning_state["game-easy"] = true;
}

void RenderHandler::gameHardInit() {
    initTower(1000, 50);

    sf::Texture *texture = initTexture("enemies");
    texture->loadFromFile(AssetsMap::get("enemies-tile-set"));
    initEnemyGenerator(texture);

    clock.restart();
    cleaning_state["game-hard"] = false;
}

void RenderHandler::gameHardClear() {
    delete enemy_generator;
    delete tower;
    cleaning_state["game-hard"] = true;
}

void RenderHandler::gameHackedInit() {
    initTower(10000, INFINITY);

    sf::Texture *texture = initTexture("enemies");
    texture->loadFromFile(AssetsMap::get("enemies-tile-set"));
    initEnemyGenerator(texture);

    clock.restart();
    cleaning_state["game-hacked"] = false;
}

void RenderHandler::gameHackedClear() {
    delete enemy_generator;
    delete tower;
    cleaning_state["game-hacked"] = true;
}

void RenderHandler::gameOverInit() {

}

void RenderHandler::gameOverClear() {

}

void RenderHandler::initEnemyGenerator(sf::Texture *texture) {
    bool game_type = *state != GAME_STATE::game_difficulty_easy;
    enemy_generator = new EnemyGenerator(*state, &enemies, tower, {
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 0, Enemy::Stats {75,135,0,13,900,800},
                ENEMY_TYPE::enemy1),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 1, Enemy::Stats {100,115,0,15,1000,900},
                ENEMY_TYPE::enemy2),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 2, Enemy::Stats {130,100,0,20,1250,1150},
                ENEMY_TYPE::enemy3),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 3, Enemy::Stats {150,85,0,22,1500,1400},
                ENEMY_TYPE::enemy4),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 4, Enemy::Stats {200,70,0,30,2000,1900},
                ENEMY_TYPE::enemy5),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 5, Enemy::Stats {400,100,0,100,4500,3500},
                ENEMY_TYPE::boss1),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 6, Enemy::Stats {2000,50,0,300,8000,6500},
                ENEMY_TYPE::boss2),
        new Enemy(game_type ? maps[1] : maps[0], !game_type, texture, 7, Enemy::Stats {300,200,0,175,2000,1000},
                ENEMY_TYPE::boss3, true, 8, 35),
    });
}

void RenderHandler::initTower(int hp, double coin) {
    factory.instantiateTexture("heart", AssetsMap::get("heart"));
    factory.instantiateTexture("coin", AssetsMap::get("coin"));
    factory.instantiateTexture("hud-bg", AssetsMap::get("hud-bg"));

    tower = new Tower(&comfortaa, hp, coin, {
            {"heart", factory.instantiateSprite("heart", "heart")},
            {"coin", factory.instantiateSprite("coin", "coin")},
            {"hud-bg", factory.instantiateSprite("hud-bg", "hud-bg")}
    });
    new TowerLPObserver(tower, state);
}

void RenderHandler::loopRender(const std::vector<sf::Drawable *>& container) {
    for(sf::Drawable *drawable : container) { window->draw(*drawable); }
}
