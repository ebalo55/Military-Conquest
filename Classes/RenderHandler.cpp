//
// Created by ebalo on 20/03/20.
//

#include "RenderHandler.h"
#include "Observers/TowerLPObserver.h"

RenderHandler::RenderHandler(const sptr<EventHandler>& event_handler) {
    this->event_handler = event_handler;

    // Global initialization
    window = event_handler->getRenderWindow();
    state = event_handler->getGameState();
    comfortaa = std::make_shared<sf::Font>();
    comfortaa->loadFromFile(AssetsMap::get("font-comfortaa"));
    maps = {std::make_shared<MapEasy>(), std::make_shared<MapHard>()};
    factory.setEventHandler(event_handler);
    factory.setWindow(window);
}

RenderHandler::~RenderHandler() = default;

void RenderHandler::handle() {
    window->clear(sf::Color(0x75, 0x8d, 0x1f));            // Clear the window
    switch(*state) {
        case initial_screen:
            if (cleaning_state["splash"]) { splashInit(); }
            splashScreen();
            break;
        case difficulty_screen:
            if (cleaning_state["difficult"]) { difficultInit(); }
            if (!cleaning_state["splash"]) { splashClear(); }
            if (!cleaning_state["game-over"]) { gameOverClear(); }
            difficultScreen();
            break;
        case game_difficulty_easy:
        case game_difficulty_hard:
        case game_difficulty_hacked:
            if (cleaning_state["game"]) { gameInit(); }
            if (!cleaning_state["difficult"]) { difficultClear(); }
            gameScreen();
            break;
        case game_over:
            if (cleaning_state["game-over"]) { gameOverInit(); }
            if (!cleaning_state["game"]) { gameClear(); }
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

void RenderHandler::gameScreen() {
    window->draw(*state == GAME_STATE::game_difficulty_easy ? *(maps[0]) : *(maps[1]));

    int elapsed_time = clock.restart().asMilliseconds();
    enemy_generator->tick(elapsed_time);

    for(const sptr<Enemy>& enemy : *enemies) {
        if(!enemy->getDeletedState()) {
            enemy->move(elapsed_time);
            window->draw(*enemy);
        }
        else {
            to_remove.push_back(enemy);
        }
    }

    tower->syncStats();
    window->draw(*tower);
    window->draw(*turret_generator);
    /*window->draw(*bullet);
    bullet->move(elapsed_time);*/
    enemy_generator->syncEnemies();
    loopRemove();
}

void RenderHandler::gameOverScreen() {
    window->draw(*(maps[1]));
}

void RenderHandler::splashInit() {
    factory.instantiateTexture("logo", AssetsMap::get("logo"));

    sptr<sf::Sprite> sprite = factory.instantiateSprite("logo", "logo");
    sprite->setPosition((WINDOW_WIDTH - sprite->getLocalBounds().width) / 2,
            (WINDOW_HEIGHT - sprite->getLocalBounds().height) / 2);

    sptr<ButtonRect> start = factory.instantiateButtonRect("start",
            sf::Vector2i{75, 40},
            comfortaa,
            "Start",
            18,
            sf::Color(0, 0, 0),
            sf::Color(0, 0, 0),
            sf::Vector2f{(WINDOW_WIDTH - 75) / 2, WINDOW_HEIGHT - 100});
    factory.linkEvent(start,
            new StartButtonHoverEvent(start, false),
            new StartButtonHoverEvent(start),
            new StartButtonClickEvent(start, state.get()));

    cleaning_state["splash"] = false;
}

void RenderHandler::splashClear() {
    factory.clear(DrawableFactory::Maps::textures, {"logo"});
    factory.clear(DrawableFactory::Maps::sprites, {"logo"});
    /*factory.clear(DrawableFactory::Maps::rect_buttons, {"start"});
    factory.purgeButton("start");*/

    cleaning_state["splash"] = true;
}

void RenderHandler::difficultInit() {
    factory.instantiateTexture("rounded-box", AssetsMap::get("rounded-box"));

    sptr<sf::Sprite> sprite = factory.instantiateSprite("rounded-box", "rounded-box");
    sprite->setPosition((WINDOW_WIDTH - sprite->getLocalBounds().width) / 2,
                        (WINDOW_HEIGHT - sprite->getLocalBounds().height) / 2);

    sptr<sf::Text> text = factory.instantiateText("title",
            comfortaa,
            "Choose a difficulty to start playing the game",
            sf::Vector2f{0, 0},
            35,
            sf::Color(0, 0, 0),
            sf::Text::Style::Bold);
    text->setPosition(sf::Vector2f{
            sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width - text->getLocalBounds().width) / 2,
            sprite->getGlobalBounds().top + 25});

    factory.instantiateText("difficult-easy",
            comfortaa,
            "One path only, standard enemies and\n  resources, bosses every 10 waves.",
            sf::Vector2f{sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 150},
            26);
    factory.instantiateText("difficult-hard",
            comfortaa,
            "Multiple paths, stronger enemies and\n  less resources,bosses every 5 waves.",
            sf::Vector2f{sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 300},
            26);
    factory.instantiateText("difficult-hacked",
            comfortaa,
            "Multiple paths, stronger enemies and\n  unlimited resources, bosses every 5 waves.",
            sf::Vector2f{sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 450},
            26);

    sptr<ButtonRect> btn = factory.instantiateButtonRect("difficult-easy",
            sf::Vector2i{75, 40},
            comfortaa,
            "Easy",
            18,
            sf::Color(0x3f, 0xb9, 0x1f),
            sf::Color(0x49, 0xd1, 0x41),
            sf::Vector2f{sprite->getGlobalBounds().left +
            sprite->getGlobalBounds().width - 125,
            sprite->getGlobalBounds().top + 160});
    factory.linkEvent(btn,
            new DifficultButtonHoverEvent(btn, false, sf::Color(0x49, 0xd1, 0x41)),
            new DifficultButtonHoverEvent(btn, true, sf::Color(0xee, 0xee, 0xee)),
            new DifficultButtonClickEvent(btn, state.get(), GAME_STATE::game_difficulty_easy));

    btn = factory.instantiateButtonRect("difficult-hard",
            sf::Vector2i{75, 40},
            comfortaa,
            "Hard",
            18,
            sf::Color(0xcc, 0x30, 0x10),
            sf::Color(0xee, 0x50, 0x30),
            sf::Vector2f{
        sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125,
        sprite->getGlobalBounds().top + 310});
    factory.linkEvent(btn,
            new DifficultButtonHoverEvent(btn, false, sf::Color(0xee, 0x50, 0x30)),
            new DifficultButtonHoverEvent(btn, true, sf::Color(0xee, 0xee, 0xee)),
            new DifficultButtonClickEvent(btn, state.get(), GAME_STATE::game_difficulty_hard));

    btn = factory.instantiateButtonRect("difficult-hacked",
            sf::Vector2i{75, 40},
            comfortaa,
            "Hacked",
            18,
            sf::Color(0xcc, 0xcc, 0x30),
            sf::Color(0x99, 0x99, 0x30),
            sf::Vector2f{sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125,sprite->getGlobalBounds().top + 460});
    factory.linkEvent(btn,
            new DifficultButtonHoverEvent(btn, false, sf::Color(0x99, 0x99, 0x30)),
            new DifficultButtonHoverEvent(btn, true, sf::Color(0x20, 0x20, 0x20)),
            new DifficultButtonClickEvent(btn, state.get(), GAME_STATE::game_difficulty_hacked));

    cleaning_state["difficult"] = false;
}

void RenderHandler::difficultClear() {
    factory.clear(DrawableFactory::Maps::textures, {"rounded-box"});
    factory.clear(DrawableFactory::Maps::sprites, {"rounded-box"});
    factory.clear(DrawableFactory::Maps::texts, {"title", "difficult-easy", "difficult-hard", "difficult-hacked"});
    /*factory.purgeButton({"difficult-easy", "difficult-hard", "difficult-hacked"});
    factory.clear(DrawableFactory::Maps::rect_buttons, {"difficult-easy", "difficult-hard", "difficult-hacked"});*/

    cleaning_state["difficult"] = true;
}

void RenderHandler::gameInit() {
    initTower(*state == GAME_STATE::game_difficulty_hacked ? 10000 : 1000,
              *state == GAME_STATE::game_difficulty_easy ? 100 : *state == GAME_STATE::game_difficulty_hard ? 50 : INFINITY);

    initEnemyGenerator();
    enemy_generator->genFixedNumber(ENEMY_TYPE::boss3, 5);

    turret_generator = std::make_shared<TurretGenerator>(TurretGenerator(window, comfortaa, event_handler,
            *state == GAME_STATE::game_difficulty_easy ? maps[0] : maps[1],
            *state == GAME_STATE::game_difficulty_easy, tower));

    //bullet = new Bullet(-300, 0, 10, sf::Vector2f {240, 95});

    clock.restart();
    cleaning_state["game"] = false;
}

void RenderHandler::gameClear() {
    enemy_generator.reset();
    tower.reset();
    factory.clear(DrawableFactory::Maps::textures, {"enemies", "turret-tile"});

    cleaning_state["game"] = true;
}

void RenderHandler::gameOverInit() {

}

void RenderHandler::gameOverClear() {

}

void RenderHandler::initEnemyGenerator() {
    enemies = std::make_shared<std::forward_list<sptr<Enemy>>>();
    enemy_generator = std::make_shared<EnemyGenerator>(EnemyGenerator(*state, enemies, tower, maps, *state == GAME_STATE::game_difficulty_easy));
}

void RenderHandler::initTower(int hp, double coin) {
    tower = std::make_shared<Tower>(Tower(comfortaa, hp, coin));
    new TowerLPObserver(tower, state);
}

void RenderHandler::loopRender(const std::vector<sptr<sf::Drawable>> &container) {
    for(const sptr<sf::Drawable>& drawable : container) {
        window->draw(*drawable);
    }
}

void RenderHandler::loopRemove() {
    for(sptr<Enemy> enemy : to_remove) {
        enemy.reset();
    }
    to_remove.clear();
}
