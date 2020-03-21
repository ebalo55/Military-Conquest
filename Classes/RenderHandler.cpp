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
    window = event_handler->getRenderWindow();
    state = event_handler->getGameState();

    maps = {new MapEasy(), new MapHard()};
    logo_texture.loadFromFile(AssetsMap::get("logo"));
    logo.setTexture(logo_texture);
    logo.setPosition((WINDOW_WIDTH - logo.getLocalBounds().width) / 2, (WINDOW_HEIGHT - logo.getLocalBounds().height) / 2);

    comfortaa.loadFromFile(AssetsMap::get("font-comfortaa"));

    start.setSize(75, 40)->setPosition((WINDOW_WIDTH - 75) / 2, WINDOW_HEIGHT - 100)->setLabel(&comfortaa, "Start", 18);
    event_handler->registerButton(&start);

    new MouseOutObserver(&start, new StartButtonHoverEvent(&start, false), window);
    new MouseHoverObserver(&start, new StartButtonHoverEvent(&start), window);
    new MouseClickObserver(&start, new StartButtonClickEvent(&start, state), window);
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
            window->draw(*(maps[1]));
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
    //std::cout << "start.hasMouseHover: " << start.hasMouseHover(window) << std::endl;
}