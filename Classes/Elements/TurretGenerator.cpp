//
// Created by ebalo on 24/03/20.
//

#include "TurretGenerator.h"
#include "../Events/TurretMenuButtonClick.h"
#include "../Events/DifficultButtonHover.h"
#include "../Events/CraftTurretButtonClick.h"

TurretGenerator::TurretGenerator(const sptr<sf::RenderWindow>& window, sptr<sf::Font> font, const sptr<EventHandler>& eventHandler, sptr<Map> map, bool is_easy, const sptr<Tower>& tower) {
    factory = std::make_shared<DrawableFactory>();
    factory->setEventHandler(eventHandler);
    factory->setWindow(window);

    this->window = window;
    this->font = font;
    this->eventHandler = eventHandler;
    this->map = map;

    sptr<sf::Texture> texture = factory->instantiateTexture("turret-tile", AssetsMap::get("tile-set"));

    // Initialize instances using the configuration file
    sptr<Config> config = Config::getInstance();
    for(TurretStats stats : config->getAllTurretStats()) {
        initialized_instances.push_back(std::make_shared<Turret>(tower, texture, is_easy ? stats : stats *1.5));
    }

    factory->instantiateTexture("right-arrow", AssetsMap::get("right-arrow"));
    factory->instantiateTexture("left-arrow", AssetsMap::get("left-arrow"));

    sptr<ButtonIcon> button_icon = factory->instantiateButtonIcon("right-arrow", "right-arrow",
                                                                  sf::Vector2f{(float) Config::getWidth() - 20,
                                                                               (float) Config::getHeight() - 20});
    factory->linkEvent(button_icon,
                       std::unique_ptr<Event>(new IconButtonHoverEvent(button_icon)),
                       std::unique_ptr<Event>(new IconButtonHoverEvent(button_icon, false)),
                       std::unique_ptr<Event>(new TurretMenuButtonClickEvent(button_icon, this)));

    button_icon = factory->instantiateButtonIcon("left-arrow", "left-arrow",
                                                 sf::Vector2f{(float) Config::getWidth() - 20,
                                                              (float) Config::getHeight() - 20});
    new MouseHoverObserver(button_icon, std::unique_ptr<Event>(new IconButtonHoverEvent(button_icon)), window);
    new MouseOutObserver(button_icon, std::unique_ptr<Event>(new IconButtonHoverEvent(button_icon, false)), window);
    new MouseClickObserver(button_icon,
                           std::unique_ptr<Event>(new TurretMenuButtonClickEvent(button_icon, this, false)), window);

    factory->instantiateTexture("craft", AssetsMap::get("craft"));
    factory->instantiateTexture("craft-close", AssetsMap::get("craft-close"));
    factory->instantiateTexture("hud-bg", AssetsMap::get("vertical-hud-bg"));
    factory->instantiateSprite("hud-bg", "hud-bg",
                               sf::Vector2f{(float) Config::getWidth() - 200, (float) Config::getHeight() - 310});

    generateInstancesMap();
}

sptr<Turret> TurretGenerator::generate(int turret_index) {
    return std::make_shared<Turret>(Turret(initialized_instances[turret_index]));
}

void TurretGenerator::generateInstancesMap() {
    sptr<sf::Sprite> sprite;
    sptr<ButtonRect> button;
    sf::Color color(0xdd, 0xdd, 0xdd);
    std::stringstream stringstream;

    int x = 0,
        positional_factor;

    std::map<std::string, int> loopable_turret_type = Config::getLoopableTurretType();

    for (const sptr<Turret>& turret : initialized_instances) {
        int type = turret->getType();

        /* Generate instances map for an arbitrary number of instances (read from config.json)
         * This step could be avoided but as it's impossible to know if the instances are ordered in the configuration
         * this step become necessary
         */
        for (std::pair<std::string, int> line : loopable_turret_type) {
            if (type == line.second) { initialized_instances_map[line.second] = x; }
        }

        positional_factor = (3 - type % 3) * 100;

        sprite = turret->getSprite();
        sprite->setPosition(
                sf::Vector2f{Config::getWidth() - 185, (float) (Config::getHeight() - (-5 + positional_factor))});

        factory->instantiateText(turret->getTurretName(),
                                 font,
                                 turret->getTurretName(),
                                 sf::Vector2f{Config::getWidth() - 140,
                                              (float) (Config::getHeight() - (-5 + positional_factor))},
                                 15,
                                 color,
                                 sf::Text::Style::Bold);

        stringstream.str("");
        stringstream << "Radius: " << turret->getRadius();
        factory->instantiateText(turret->getTurretName() + "-radius",
                                 font,
                                 stringstream.str(),
                                 sf::Vector2f{Config::getWidth() - 140,
                                              (float) (Config::getHeight() - (-35 + positional_factor))},
                                 12,
                                 color);

        stringstream.str("");
        stringstream << "Power: " << turret->getPower();
        factory->instantiateText(turret->getTurretName() + "-power",
                                 font,
                                 stringstream.str(),
                                 sf::Vector2f{Config::getWidth() - 175,
                                              (float) (Config::getHeight() - (-50 + positional_factor))},
                                 12,
                                 color);

        stringstream.str("");
        stringstream << "Fire rate: " << turret->getFireRate() << " shots/s";
        factory->instantiateText(turret->getTurretName() + "-fire-rate",
                                 font,
                                 stringstream.str(),
                                 sf::Vector2f{Config::getWidth() - 175,
                                              (float) (Config::getHeight() - (-65 + positional_factor))},
                                 12,
                                 color);

        stringstream.str("");
        stringstream << "Cost: " << turret->getCost();
        factory->instantiateText(turret->getTurretName() + "-cost",
                                 font,
                                 stringstream.str(),
                                 sf::Vector2f{Config::getWidth() - 175,
                                              (float) (Config::getHeight() - (-80 + positional_factor))},
                                 12,
                                 color);

        button = factory->instantiateButtonRect(turret->getTurretName() + "-craft",
                                                sf::Vector2i{30, 30},
                                                font,
                                                "",
                                                0,
                                                sf::Color(0x40, 0xb8, 0x68),
                                                sf::Color(0, 0, 0),
                                                sf::Vector2f{(float) Config::getWidth() - 40,
                                                             (float) (Config::getHeight() -
                                                                      (-35 + positional_factor))});
        new MouseHoverObserver(button, std::unique_ptr<Event>(new DifficultButtonHoverEvent(button)), window);
        new MouseOutObserver(button, std::unique_ptr<Event>(new DifficultButtonHoverEvent(button, false)), window);
        new MouseClickObserver(button, std::unique_ptr<Event>(new CraftTurretButtonClickEvent(button, window, this, x)),
                               window);

        factory->instantiateSprite(turret->getTurretName() + "-craft", "craft",
                                   sf::Vector2f{(float) Config::getWidth() - 35,
                                                (float) (Config::getHeight() - (-40 + positional_factor))});
        factory->instantiateSprite(turret->getTurretName() + "-craft-close", "craft-close",
                                   sf::Vector2f{(float) Config::getWidth() - 35,
                                                (float) (Config::getHeight() - (-40 + positional_factor))});

        if (x < 3) { eventHandler->registerButton(button); }
        x++;
    }
}

void TurretGenerator::renderTurretMenu(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*factory->getSprite("hud-bg"), states);

    if (translate_left_arrow) {
        factory->getButtonIcon("left-arrow")->setPosition(Config::getWidth() - 20, Config::getHeight() - 20);
    }

    // Show all the infos of the turret into the turret menu
    std::string name;
    int showable = current_page * 3,
            loaded_turret = Config::getLoadedTurretNumber();
    for (int i = (current_page - 1) * 3; i < (loaded_turret >= showable ? showable : loaded_turret); i++) {
        name = initialized_instances[i]->getTurretName();
        target.draw(*initialized_instances[i]->getSprite(), states);

        for (std::string str : {"", "-radius", "-power", "-fire-rate", "-cost"}) {
            target.draw(*factory->getText(name + str), states);
        }
        target.draw(*factory->getButtonRect(name + "-craft"), states);

        if (!turret_placing_loop || selected_turret != i) {
            target.draw(*factory->getSprite(name + "-craft"), states);
        } else if (turret_placing_loop && selected_turret == i) {
            target.draw(*factory->getSprite(name + "-craft-close"), states);
        }
    }

    if (factory->has(DrawableFactory::Maps::sprites, "craft_turret_sprite")) {
        target.draw(*factory->getSprite("craft_turret_sprite"));
    }

    if (render_left_arrow) {
        target.draw(*factory->getButtonIcon("left-arrow"), states);
    }
    if (render_right_arrow) {
        target.draw(*factory->getButtonIcon("right-arrow"), states);
    }
}

void TurretGenerator::renderTurretAvailableLocations(sf::RenderTarget &target) const {
    map->generate(sf::Vector2u(40, 40), map->getMap(), map->getMapWidth(), map->getMapHeight(), true);
}

void TurretGenerator::selectTurret(TURRET_TYPE turret) {
    selected_turret =
            turret == ::turret1 ? turret1 :
            turret == ::turret2 ? turret2 :
            turret == ::turret3 ? turret3 :
            turret == ::turret4 ? turret4 : turret5;
}

void TurretGenerator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    showReachedAchievement();

    for (std::pair<std::string, sptr<sf::Drawable>> line : drawable_map) {
        target.draw(*line.second);
    }

    renderTurretMenu(target, states);
    if (turret_placing_loop) { renderTurretAvailableLocations(target); }

}

void TurretGenerator::switchMenuPage(bool forward) {
    translate_left_arrow = false;

    if (forward) {
        current_page++;
        computeSpriteSwitching();

        // Check if the left arrow should be visible in the case it should be assert the controller
        if (!render_left_arrow && ((Config::getLoadedTurretNumber() < current_page * 3 && current_page != 1) ||
                                   Config::getLoadedTurretNumber() > current_page * 3)) {
            factory->getButtonIcon("left-arrow")->setPosition(Config::getWidth() - 45, Config::getHeight() - 20);
            factory->linkButton("left-arrow", false);
            render_left_arrow = true;
        }

        // Check whether the right arrow should be visible in the case it should not negate the controller
        if (current_page * 3 > Config::getLoadedTurretNumber()) {
            /* In order to avoid the broadcasting of the click event to the left arrow button the translation is done on the next frame
             * by the assertion of translate_left_arrow which will trigger the translation in "renderTurretMenu"
             */
            translate_left_arrow = true;

            factory->unlinkButton("right-arrow", false);
            render_right_arrow = false;

            // Mark the right arrow link control as false in order to let the left click re-link the button
            right_arrow_linked = false;
        }
    } else {
        current_page--;

        computeSpriteSwitching(false);

        // Check if the left arrow should be visible in the case it should not negate the controller
        if ((current_page - 1) * 3 <= 0) {
            factory->unlinkButton("left-arrow", false);
            render_left_arrow = false;
        }

        // Check if the right arrow should be visible in the case it should assert the controller
        if (current_page * 3 < Config::getLoadedTurretNumber()) {
            // Avoid multiple buttons linkage (and subsequent unwanted page jumps)
            if (!right_arrow_linked) {
                factory->linkButton("right-arrow", false);
                right_arrow_linked = true;
            }

            factory->getButtonIcon("left-arrow")->setPosition(Config::getWidth() - 45, Config::getHeight() - 20);
            render_right_arrow = true;
        }
    }
}

void TurretGenerator::setTurretPlacement(bool state) {
    turret_placing_loop = state;
    if (!turret_placing_loop) {
        map->generate(sf::Vector2u(40, 40), map->getMap(), map->getMapWidth(), map->getMapHeight());
    }
}

sptr<EventHandler> TurretGenerator::getEventHandler() {
    return eventHandler;
}

sptr<sf::Sprite> TurretGenerator::cloneTurretSprite(int index) {
    destroyCraftedTurretSprite();
    selected_turret = index;

    return factory->instantiateSprite("craft_turret_sprite",
            initialized_instances[index]->getTexture(),
            (sf::Vector2f) sf::Mouse::getPosition(),
            sf::IntRect{(5 + index) * 40, 0, 40, 40});
}

void TurretGenerator::destroyCraftedTurretSprite() {
    if (factory->has(DrawableFactory::Maps::sprites, "craft_turret_sprite")) {
        factory->clear(DrawableFactory::Maps::sprites, {"craft_turret_sprite"});
    }
}

void TurretGenerator::setCraftVirtualButton(sptr<Button> btn) {
    craft_virtual_button = btn;
}

Map *TurretGenerator::getMap() {
    return map.get();
}

int TurretGenerator::getSelectedTurret() {
    return selected_turret;
}

sptr<sf::Font> TurretGenerator::getFont() {
    return font;
}

void TurretGenerator::registerTurret(const sptr<Turret>& turret) {
    turrets.push_back(turret);
}

sptr<std::vector<sptr<Turret>>> TurretGenerator::getRegisteredTurrets() {
    return std::make_shared<std::vector<sptr<Turret>>>(turrets);
}

std::vector<sptr<Bullet>> TurretGenerator::getBullets() {
    std::vector<sptr<Bullet>> bullets;
    for(const sptr<Turret>& turret : turrets) {
        for(const sptr<Bullet>& bullet : *turret->getBulletsList()) {
            bullets.push_back(bullet);
        }
    }
    return bullets;
}

const std::vector<sptr<Turret>> &TurretGenerator::getRegisteredTurretsAsReference() {
    return turrets;
}

void TurretGenerator::showReachedAchievement() const {
    if(showing_achievement && achievement_clock.getElapsedTime().asSeconds() <= 10) {
        window->draw(*factory->getSprite("ribbon"));
        window->draw(*factory->getText("ribbon-title"));
        window->draw(*factory->getText("ribbon-body"));
    }
}

void TurretGenerator::setUpReachedAchievement(std::string title, std::string body) {
    if (!showing_achievement) {
        factory->instantiateTexture("ribbon", AssetsMap::get("ribbon"));
        factory->instantiateSprite("ribbon", "ribbon",
                                   {(float) (Config::getWidth() - 660) / 2, (float) Config::getHeight() / 2 - 300});
        factory->instantiateText("ribbon-title", font, "", {0, 0}, 25);
        factory->instantiateText("ribbon-body", font, "", {0, 0}, 15);
    }

    sptr<sf::Text> title_place = factory->getText("ribbon-title");
    title_place->setString(title);
    title_place->setPosition((float) (Config::getWidth() - 660) / 2 + title_place->getLocalBounds().width * 2 / 3,
                             (float) achievement_title_vertical_align);
    sptr<sf::Text> body_place = factory->getText("ribbon-body");
    body_place->setString(body);
    body_place->setPosition((float) (Config::getWidth() - 660) / 2 + 120, (float) achievement_body_vertical_align);

    showing_achievement = true;
    achievement_clock.restart();
}

void TurretGenerator::computeSpriteSwitching(bool forward) {
    int previous = (current_page - 1) * 3,
            current = current_page * 3,
            next = (current_page + 1) * 3,

            loaded_turrets = Config::getLoadedTurretNumber();

    // Get the maximum number of turret showable into the current page of menu, than link them
    std::vector<std::string> link_buttons;
    for (int i = previous; i < loaded_turrets && i < current; i++) {
        link_buttons.push_back(initialized_instances[i]->getTurretName() + "-craft");
    }
    factory->linkButton(link_buttons);

    if (forward) {
        // Unlink all the turrets in the previous page
        link_buttons.clear();
        for (int i = 1; i <= 3; i++) {
            link_buttons.push_back(initialized_instances[previous - i]->getTurretName() + "-craft");
        }
        factory->unlinkButton(link_buttons);
    } else {
        // Unlink all the turrets in the next page
        link_buttons.clear();
        for (int i = current; i < loaded_turrets && i < next; i++) {
            link_buttons.push_back(initialized_instances[i]->getTurretName() + "-craft");
        }
        factory->unlinkButton(link_buttons);
    }
}
