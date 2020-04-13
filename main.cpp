#include <memory>
#include "Classes/EventHandler.h"
#include "Classes/RenderHandler.h"
#include "Classes/States/windowSize.h"

int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    std::shared_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, mode.bitsPerPixel), "Military Conquest"));
    window->setPosition(sf::Vector2i {(int)(mode.width - WINDOW_WIDTH) / 2, (int)(mode.height - WINDOW_HEIGHT) / 2});                // Center window
    window->setVerticalSyncEnabled(true);                                                                                // Sync framerate with the window

    std::shared_ptr<GAME_STATE> game_state = std::make_shared<GAME_STATE>(GAME_STATE::game_difficulty_easy);

    std::shared_ptr<EventHandler> eventHandler( new EventHandler(window, game_state));
    RenderHandler renderHandler(eventHandler);
    while(window->isOpen()) {
        eventHandler->handle();
        renderHandler.handle();
    }
    return 0;
}
