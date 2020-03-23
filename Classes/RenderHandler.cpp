//
// Created by ebalo on 20/03/20.
//

#include <zconf.h>
#include "RenderHandler.h"

RenderHandler::RenderHandler(EventHandler *event_handler) {
    this->event_handler = event_handler;
    // Global initialization
    window = event_handler->getRenderWindow();
    state = event_handler->getGameState();
    comfortaa.loadFromFile(AssetsMap::get("font-comfortaa"));
    maps = {new MapEasy(), new MapHard()};
}

RenderHandler::~RenderHandler() {
    for(int i = 0; i < maps.size(); i++) { delete maps[i]; }
}

void RenderHandler::handle() {
    window->clear();            // Clear the window
    switch(*state) {
        case initial_screen:
            splashInit();
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
    window->draw(*(maps[1]));
    window->draw(*getSprite("logo"));
    window->draw(*getButtonRect("start"));
}

void RenderHandler::difficultScreen() {
    window->draw(*(maps[1]));
    window->draw(*getSprite("rounded-box"));
    window->draw(*getText("title"));
    window->draw(*getText("difficult-easy"));
    window->draw(*getText("difficult-hard"));
    window->draw(*getText("difficult-hacked"));
    window->draw(*getButtonRect("difficult-easy"));
    window->draw(*getButtonRect("difficult-hard"));
    window->draw(*getButtonRect("difficult-hacked"));
}

void RenderHandler::gameEasyScreen() {
    window->draw(*(maps[0]));
    enemy->move(clock.getElapsedTime().asMilliseconds());
    window->draw(*enemy);
    clock.restart();
}

void RenderHandler::gameHardScreen() {
    window->draw(*(maps[1]));
    enemy->move(clock.getElapsedTime().asMilliseconds());
    window->draw(*enemy);
    clock.restart();
}

void RenderHandler::gameHackedScreen() {
    window->draw(*(maps[1]));
}

void RenderHandler::gameOverScreen() {
    window->draw(*(maps[1]));
}

sf::Sprite *RenderHandler::initSprite(const std::string& name) {
    sprites_map[name] = sf::Sprite();
    return &sprites_map[name];
}

sf::Sprite *RenderHandler::getSprite(const std::string& name) {
    return &sprites_map[name];
}

sf::Texture *RenderHandler::initTexture(const std::string& name) {
    textures_map[name] = sf::Texture();
    return &textures_map[name];
}

sf::Texture *RenderHandler::getTexture(const std::string& name) {
    return &textures_map[name];
}

ButtonRect *RenderHandler::initButtonRect(const std::string& name) {
    rect_buttons_map[name] = ButtonRect();
    return &rect_buttons_map[name];
}

ButtonRect *RenderHandler::getButtonRect(const std::string& name) {
    return &rect_buttons_map[name];
}

sf::Text *RenderHandler::initText(const std::string &name) {
    texts_map[name] = sf::Text();
    return &texts_map[name];
}

sf::Text *RenderHandler::getText(const std::string &name) {
    return &texts_map[name];
}

void RenderHandler::splashInit() {
    sf::Texture *texture = initTexture("logo");
    texture->loadFromFile(AssetsMap::get("logo"));

    sf::Sprite *sprite = initSprite("logo");
    sprite->setTexture(*texture);
    sprite->setPosition((WINDOW_WIDTH - sprite->getLocalBounds().width) / 2, (WINDOW_HEIGHT - sprite->getLocalBounds().height) / 2);

    ButtonRect *start = initButtonRect("start");
    start->setSize(75, 40)->setPosition((WINDOW_WIDTH - 75) / 2, WINDOW_HEIGHT - 100)->setLabel(&comfortaa, "Start", 18);
    event_handler->registerButton(start);
    new MouseOutObserver(start, new StartButtonHoverEvent(start, false), window);
    new MouseHoverObserver(start, new StartButtonHoverEvent(start), window);
    new MouseClickObserver(start, new StartButtonClickEvent(start, state), window);

    cleaning_state["splash"] = false;
}

void RenderHandler::splashClear() {
    textures_map.erase("logo");
    sprites_map.erase("logo");
    event_handler->deleteButton(getButtonRect("start"));
    rect_buttons_map.erase("start");
    cleaning_state["splash"] = true;
}

void RenderHandler::difficultInit() {
    sf::Texture *texture = initTexture("rounded-box");
    texture->loadFromFile(AssetsMap::get("rounded-box"));

    sf::Sprite *sprite = initSprite("rounded-box");
    sprite->setTexture(*texture);
    sprite->setPosition((WINDOW_WIDTH - sprite->getLocalBounds().width) / 2, (WINDOW_HEIGHT - sprite->getLocalBounds().height) / 2);

    sf::Text *text = initText("title");
    text->setFont(comfortaa);
    text->setCharacterSize(35);
    text->setString("Choose a difficulty to start playing the game");
    text->setStyle(sf::Text::Style::Bold);
    text->setFillColor(sf::Color(0, 0, 0));
    text->setPosition(sf::Vector2f {sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width - text->getLocalBounds().width) / 2, sprite->getGlobalBounds().top + 25});

    text = initText("difficult-easy");
    text->setFont(comfortaa);
    text->setCharacterSize(26);
    text->setString("One path only, standard enemies and\n  resources, bosses every 10 waves.");
    text->setFillColor(sf::Color(0, 0, 0));
    text->setPosition(sf::Vector2f {sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 150});

    text = initText("difficult-hard");
    text->setFont(comfortaa);
    text->setCharacterSize(26);
    text->setString("Multiple paths, stronger enemies and\n  less resources,bosses every 5 waves.");
    text->setFillColor(sf::Color(0, 0, 0));
    text->setPosition(sf::Vector2f {sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 300});

    text = initText("difficult-hacked");
    text->setFont(comfortaa);
    text->setCharacterSize(26);
    text->setString("Multiple paths, stronger enemies and\n  unlimited resources, bosses every 5 waves.");
    text->setFillColor(sf::Color(0, 0, 0));
    text->setPosition(sf::Vector2f {sprite->getGlobalBounds().left + 50, sprite->getGlobalBounds().top + 450});

    ButtonRect *button = initButtonRect("difficult-easy");
    button->setSize(75, 40);
    button->setColor(sf::Color(0x3f, 0xb9, 0x1f));
    button->setLabelColor(sf::Color(0x49, 0xd1, 0x41));
    button->setPosition(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125, sprite->getGlobalBounds().top + 160);
    button->setLabel(&comfortaa, "Easy", 18);
    event_handler->registerButton(button);
    new MouseOutObserver(button, new DifficultButtonHoverEvent(button, false, sf::Color(0x49, 0xd1, 0x41)), window);
    new MouseHoverObserver(button, new DifficultButtonHoverEvent(button, true, sf::Color(0xee, 0xee, 0xee)), window);
    new MouseClickObserver(button, new DifficultButtonClickEvent(button, state, GAME_STATE::game_difficulty_easy), window);

    button = initButtonRect("difficult-hard");
    button->setSize(75, 40);
    button->setColor(sf::Color(0xcc, 0x30, 0x10));
    button->setLabelColor(sf::Color(0xee, 0x50, 0x30));
    button->setPosition(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125, sprite->getGlobalBounds().top + 310);
    button->setLabel(&comfortaa, "Hard", 18);
    event_handler->registerButton(button);
    new MouseOutObserver(button, new DifficultButtonHoverEvent(button, false, sf::Color(0xee, 0x50, 0x30)), window);
    new MouseHoverObserver(button, new DifficultButtonHoverEvent(button, true, sf::Color(0xee, 0xee, 0xee)), window);
    new MouseClickObserver(button, new DifficultButtonClickEvent(button, state, GAME_STATE::game_difficulty_hard), window);

    button = initButtonRect("difficult-hacked");
    button->setSize(75, 40);
    button->setColor(sf::Color(0xcc, 0xcc, 0x30));
    button->setLabelColor(sf::Color(0x99, 0x99, 0x30));
    button->setPosition(sprite->getGlobalBounds().left + sprite->getGlobalBounds().width - 125, sprite->getGlobalBounds().top + 460);
    button->setLabel(&comfortaa, "Hacked", 18);
    event_handler->registerButton(button);
    new MouseOutObserver(button, new DifficultButtonHoverEvent(button, false, sf::Color(0x99, 0x99, 0x30)), window);
    new MouseHoverObserver(button, new DifficultButtonHoverEvent(button, true, sf::Color(0x20, 0x20, 0x20)), window);
    new MouseClickObserver(button, new DifficultButtonClickEvent(button, state, GAME_STATE::game_difficulty_hacked), window);

    cleaning_state["difficult"] = false;
}

void RenderHandler::difficultClear() {
    textures_map.erase("rounded-box");
    sprites_map.erase("rounded-box");
    massClear(&texts_map, {"title", "difficult-easy", "difficult-hard", "difficult-hacked"});
    event_handler->deleteButton(getButtonRect("difficult-easy"));
    event_handler->deleteButton(getButtonRect("difficult-hard"));
    event_handler->deleteButton(getButtonRect("difficult-hacked"));
    massClear(&rect_buttons_map, {"difficult-easy", "difficult-hard", "difficult-hacked"});

    cleaning_state["difficult"] = true;
}

void RenderHandler::gameEasyInit() {
    sf::Texture *texture = initTexture("enemies");
    texture->loadFromFile(AssetsMap::get("enemies-tile-set"));

    enemy = new Enemy(maps[0], true, texture, 0, Enemy::Stats {1, 100, 0, 1, 1, 1}, 0);

    clock.restart();
    cleaning_state["game-easy"] = false;
}

void RenderHandler::gameEasyClear() {

}

void RenderHandler::gameHardInit() {
    sf::Texture *texture = initTexture("enemies");
    texture->loadFromFile(AssetsMap::get("enemies-tile-set"));

    enemy = new Enemy(maps[1], false, texture, 0, Enemy::Stats {1, 100, 0, 1, 1, 1}, 0);

    clock.restart();
    cleaning_state["game-hard"] = false;
}

void RenderHandler::gameHardClear() {

}

void RenderHandler::gameHackedInit() {

}

void RenderHandler::gameHackedClear() {

}

void RenderHandler::gameOverInit() {

}

void RenderHandler::gameOverClear() {

}

void RenderHandler::massClear(std::unordered_map<std::string, sf::Texture> *map, const std::vector<std::string>& names) {
    for(const std::string& name : names) { map->erase(name); }
}

void RenderHandler::massClear(std::unordered_map<std::string, sf::Sprite> *map, const std::vector<std::string>& names) {
    for(const std::string& name : names) { map->erase(name); }
}

void RenderHandler::massClear(std::unordered_map<std::string, ButtonRect> *map, const std::vector<std::string>& names) {
    for(const std::string& name : names) { map->erase(name); }
}

void RenderHandler::massClear(std::unordered_map<std::string, sf::Text> *map, const std::vector<std::string>& names) {
    for(const std::string& name : names) { map->erase(name); }
}