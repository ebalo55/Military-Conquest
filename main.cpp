#include "Classes/EventHandler.h"
#include "Classes/RenderHandler.h"
#include "Classes/States/GameState.h"
#include "Classes/States/windowSize.h"

int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, mode.bitsPerPixel), "TD-TowerDefense");
    window.setPosition(sf::Vector2i {(int)(mode.width - WINDOW_WIDTH) / 2, (int)(mode.height - WINDOW_HEIGHT) / 2});                // Center window
    window.setVerticalSyncEnabled(true);                                                                                // Sync framerate with the window

    GAME_STATE game_state = GAME_STATE::game_difficulty_easy;

    EventHandler eventHandler(&window, &game_state);
    RenderHandler renderHandler(&eventHandler);
    while(window.isOpen()) {
        eventHandler.handle();
        renderHandler.handle();
    }
    return 0;
}
