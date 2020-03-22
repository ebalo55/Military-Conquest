//
// Created by ebalo on 20/03/20.
//

#include "RenderHandler.h"
#include "States/windowSize.h"
#include "Events/StartButtonHover.h"
#include "Observers/MouseHoverObserver.h"
#include "Observers/MouseOutObserver.h"
#include "Observers/MouseClickObserver.h"
#include "Events/StartButtonClick.h"

RenderHandler::RenderHandler(EventHandler *event_handler) {
    this->event_handler = event_handler;
    // Global initialization
    window = event_handler->getRenderWindow();
    state = event_handler->getGameState();
    comfortaa.loadFromFile(AssetsMap::get("font-comfortaa"));
    maps = {new MapEasy(), new MapHard()};

    // Splash initialization
    textures_map["logo"] = sf::Texture();
    textures_map["logo"].loadFromFile(AssetsMap::get("logo"));
    sprites_map["logo"] = sf::Sprite();
    logo.setTexture(textures_map["logo"]);
    logo.setPosition((WINDOW_WIDTH - logo.getLocalBounds().width) / 2, (WINDOW_HEIGHT - logo.getLocalBounds().height) / 2);
    start.setSize(75, 40)->setPosition((WINDOW_WIDTH - 75) / 2, WINDOW_HEIGHT - 100)->setLabel(&comfortaa, "Start", 18);
    event_handler->registerButton(&start);
    new MouseOutObserver(&start, new StartButtonHoverEvent(&start, false), window);
    new MouseHoverObserver(&start, new StartButtonHoverEvent(&start), window);
    new MouseClickObserver(&start, new StartButtonClickEvent(&start, state), window);

    // Difficult initialization
    rounded_box_texture.loadFromFile(AssetsMap::get("rounded-box"));
    rounded_box.setTexture(rounded_box_texture);
    rounded_box.setPosition((WINDOW_WIDTH - rounded_box.getLocalBounds().width) / 2, (WINDOW_HEIGHT - rounded_box.getLocalBounds().height) / 2);
}

RenderHandler::~RenderHandler() {
    for(int i = 0; i < maps.size(); i++) { delete maps[i]; }
}

void RenderHandler::handle() {
    window->clear();            // Clear the window
    switch(*state) {
        case initial_screen:
            splashScreen();
            break;
        case difficulty_screen:
            difficultScreen();
            break;
        case game_difficulty_easy:
            break;
        case game_difficulty_hard:
            break;
        case game_difficulty_hacked:
            break;
        case game_over:
            break;
    }
    window->display();          // End frame and display content
}

void RenderHandler::splashScreen() {
    window->draw(*(maps[1]));
    window->draw(logo);
    window->draw(start);
}

void RenderHandler::difficultScreen() {
    window->draw(*(maps[1]));
    window->draw(rounded_box);

}

sf::Sprite *RenderHandler::initSprite(std::string name) {
    sprites_map[name] = sf::Sprite();
    return &sprites_map[name];
}

sf::Sprite *RenderHandler::getSprite(std::string name) {
    return &sprites_map[name];
}
