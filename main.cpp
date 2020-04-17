#include <memory>
#include "Classes/EventHandler.h"
#include "Classes/RenderHandler.h"
#include "Classes/States/windowSize.h"

int main() {
    /* The configuration is called the first time here as we want to take the window sizes from the configuration file
     * All subsequent call will use the same instance as this one.
     */
    std::shared_ptr<Config> config = Config::getInstance();

    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    std::shared_ptr<sf::RenderWindow> window(
            new sf::RenderWindow(sf::VideoMode(config->getWidth(), config->getHeight(), mode.bitsPerPixel),
                                 "Military Conquest"));
    window->setPosition(sf::Vector2i{(int) (mode.width - config->getWidth()) / 2,
                                     (int) (mode.height - config->getHeight()) / 2});                // Center window
    window->setFramerateLimit(
            60);                                                                                // Set maximum framerate

    std::shared_ptr<GAME_STATE> game_state = std::make_shared<GAME_STATE>(GAME_STATE::game_over);

    std::shared_ptr<EventHandler> eventHandler(new EventHandler(window, game_state));
    RenderHandler renderHandler(eventHandler);
    while (window->isOpen()) {
        eventHandler->handle();
        renderHandler.handle();
    }
    return 0;
}
