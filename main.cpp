#include "Classes/EventHandler.h"
#include "Classes/RenderHandler.h"

int main() {
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1280, 800, mode.bitsPerPixel), "TD-TowerDefense");
    window.setPosition(sf::Vector2i {(int)(mode.width - 1280) / 2, (int)(mode.height - 800) / 2});                // Center window
    window.setVerticalSyncEnabled(true);                                                                                // Sync framerate with the window

    EventHandler eventHandler(&window);
    RenderHandler renderHandler(&window);
    while(window.isOpen()) {
        eventHandler.handle();
        renderHandler.handle();
    }
    return 0;
}
