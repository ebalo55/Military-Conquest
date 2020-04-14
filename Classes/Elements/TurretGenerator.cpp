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

    this->initialized_instances = is_easy ? std::vector<sptr<Turret>> {
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    5,
                    Turret::TurretStats{8, 5, 10, 3, 80, "Turret 1"},
                    TURRET_TYPE::turret1)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    6,
                    Turret::TurretStats{10, 7, 13, 2, 90, "Turret 2"},
                    TURRET_TYPE::turret2)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    7,
                    Turret::TurretStats{15, 5, 20, 5, 100, "Turret 3"},
                    TURRET_TYPE::turret3)),
            std::make_shared<Turret>(Turret(tower,
                    texture,
                    8,
                    Turret::TurretStats{9, 10, 15, 2, 80, "Turret 4"},
                    TURRET_TYPE::turret4)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    9,
                    Turret::TurretStats{13, 6, 15, 5, 120, "Turret 5"},
                    TURRET_TYPE::turret5)),
    } : std::vector<sptr<Turret>> {
            // TODO: change the following values for the hard and hacked games
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    5,
                    Turret::TurretStats{8, 4, 10, 3, 80, "Turret 1"},
                    TURRET_TYPE::turret1)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    6,
                    Turret::TurretStats{10, 5, 13, 2, 60, "Turret 2"},
                    TURRET_TYPE::turret2)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    7,
                    Turret::TurretStats{15, 5, 20, 5, 100, "Turret 3"},
                    TURRET_TYPE::turret3)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    8,
                    Turret::TurretStats{5, 2, 7, 2, 80, "Turret 4"},
                    TURRET_TYPE::turret4)),
            std::make_shared<Turret>(Turret(
                    tower,
                    texture,
                    9,
                    Turret::TurretStats{13, 3, 15, 5, 120, "Turret 5"},
                    TURRET_TYPE::turret5)),
    };

    factory->instantiateTexture("right-arrow", AssetsMap::get("right-arrow"));
    factory->instantiateTexture("left-arrow", AssetsMap::get("left-arrow"));

    sptr<ButtonIcon> button_icon = factory->instantiateButtonIcon("right-arrow", "right-arrow",
            sf::Vector2f{WINDOW_WIDTH - 20, WINDOW_HEIGHT - 20});
    factory->linkEvent(button_icon,
            new IconButtonHoverEvent(button_icon),
            new IconButtonHoverEvent(button_icon, false),
            new TurretMenuButtonClickEvent(button_icon, this));

    button_icon = factory->instantiateButtonIcon("left-arrow", "left-arrow",sf::Vector2f{WINDOW_WIDTH - 20, WINDOW_HEIGHT - 20});
    new MouseHoverObserver(button_icon, new IconButtonHoverEvent(button_icon), window);
    new MouseOutObserver(button_icon, new IconButtonHoverEvent(button_icon, false), window);
    new MouseClickObserver(button_icon, new TurretMenuButtonClickEvent(button_icon, this), window);

    factory->instantiateTexture("craft", AssetsMap::get("craft"));
    factory->instantiateTexture("craft-close", AssetsMap::get("craft-close"));
    factory->instantiateTexture("hud-bg", AssetsMap::get("vertical-hud-bg"));
    factory->instantiateSprite("hud-bg", "hud-bg", sf::Vector2f{WINDOW_WIDTH - 200, WINDOW_HEIGHT - 310});

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

    for (const sptr<Turret>& turret : initialized_instances) {
        int hashcode = turret->getHashCode();
        if (hashcode == turret1) { initialized_instances_map[turret1] = x; }
        else if (hashcode == turret2) { initialized_instances_map[turret2] = x; }
        else if (hashcode == turret3) { initialized_instances_map[turret3] = x; }
        else if (hashcode == turret4) { initialized_instances_map[turret4] = x; }
        else if (hashcode == turret5) { initialized_instances_map[turret5] = x; }

        positional_factor = (3 - hashcode % 3) * 100;

        sprite = turret->getSprite();
        sprite->setPosition(sf::Vector2f{WINDOW_WIDTH - 185, (float) (WINDOW_HEIGHT - (-5 + positional_factor))});

        factory->instantiateText(turret->getTurretName(),
                font,
                turret->getTurretName(),
                sf::Vector2f{WINDOW_WIDTH - 140, (float) (WINDOW_HEIGHT - (-5 + positional_factor))},
                15,
                color,
                sf::Text::Style::Bold);

        stringstream.str("");
        stringstream << "Radius: " << turret->getRadius();
        factory->instantiateText(turret->getTurretName() + "-radius",
                font,
                stringstream.str(),
                sf::Vector2f{WINDOW_WIDTH - 140, (float) (WINDOW_HEIGHT - (-35 + positional_factor))},
                12,
                color);

        stringstream.str("");
        stringstream << "Power: " << turret->getPower();
        factory->instantiateText(turret->getTurretName() + "-power",
                font,
                stringstream.str(),
                sf::Vector2f{WINDOW_WIDTH - 175, (float) (WINDOW_HEIGHT - (-50 + positional_factor))},
                12,
                color);

        stringstream.str("");
        stringstream << "Fire rate: " << turret->getFireRate() << " shots/s";
        factory->instantiateText(turret->getTurretName() + "-fire-rate",
                font,
                stringstream.str(),
                sf::Vector2f{WINDOW_WIDTH - 175, (float) (WINDOW_HEIGHT - (-65 + positional_factor))},
                12,
                color);

        stringstream.str("");
        stringstream << "Cost: " << turret->getCost();
        factory->instantiateText(turret->getTurretName() + "-cost",
                font,
                stringstream.str(),
                sf::Vector2f{WINDOW_WIDTH - 175, (float) (WINDOW_HEIGHT - (-80 + positional_factor))},
                12,
                color);

        button = factory->instantiateButtonRect(turret->getTurretName() + "-craft",
                sf::Vector2i{30, 30},
                font,
                "",
                0,
                sf::Color(0x40, 0xb8, 0x68),
                sf::Color(0, 0, 0),
                sf::Vector2f{WINDOW_WIDTH - 40,(float) (WINDOW_HEIGHT - (-35 + positional_factor))});
        new MouseHoverObserver(button, new DifficultButtonHoverEvent(button), window);
        new MouseOutObserver(button, new DifficultButtonHoverEvent(button, false), window);
        new MouseClickObserver(button, new CraftTurretButtonClickEvent(button, window, this, x), window);

        factory->instantiateSprite(turret->getTurretName() + "-craft", "craft",
                                  sf::Vector2f{WINDOW_WIDTH - 35, (float) (WINDOW_HEIGHT - (-40 + positional_factor))});
        factory->instantiateSprite(turret->getTurretName() + "-craft-close", "craft-close",
                                  sf::Vector2f{WINDOW_WIDTH - 35, (float) (WINDOW_HEIGHT - (-40 + positional_factor))});

        if (x < 3) { eventHandler->registerButton(button); }
        x++;
    }
}

void TurretGenerator::renderTurretMenu(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*factory->getSprite("hud-bg"), states);

    std::string name;
    for (int i = (menu_first_page ? 0 : 3); i < (menu_first_page ? 3 : 5); i++) {
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

    target.draw(menu_first_page ? *factory->getButtonIcon("right-arrow") : *factory->getButtonIcon("left-arrow"), states);
}

void TurretGenerator::renderTurretAvailableLocations(sf::RenderTarget &target, sf::RenderStates states) const {
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
    for (std::pair<std::string, sptr<sf::Drawable>> line : drawable_map) {
        target.draw(*line.second);
    }

    renderTurretMenu(target, states);
    if (turret_placing_loop) { renderTurretAvailableLocations(target, states); }

}

void TurretGenerator::switchMenuPage() {
    menu_first_page = !menu_first_page;
    if (menu_first_page) {
        factory->linkButton({
            initialized_instances[0]->getTurretName() + "-craft",
            initialized_instances[1]->getTurretName() + "-craft",
            initialized_instances[2]->getTurretName() + "-craft"
        });
        factory->unlinkButton("left-arrow", false);
        factory->unlinkButton({
            initialized_instances[3]->getTurretName() + "-craft",
            initialized_instances[4]->getTurretName() + "-craft"
        });
        factory->linkButton("right-arrow", false);
    } else {
        factory->unlinkButton({
            initialized_instances[0]->getTurretName() + "-craft",
            initialized_instances[1]->getTurretName() + "-craft",
            initialized_instances[2]->getTurretName() + "-craft"
        });
        factory->linkButton("left-arrow", false);
        factory->linkButton({
            initialized_instances[3]->getTurretName() + "-craft",
            initialized_instances[4]->getTurretName() + "-craft"
        });
        factory->unlinkButton("right-arrow", false);
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

void TurretGenerator::moveBullets(int elapsed_time, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies) {
    for(const sptr<Turret>& turret : turrets) {
        turret->moveBullets(elapsed_time, enemies);
    }
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

void TurretGenerator::triggerBulletCollisionDetection(const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies) {
    /* The following code is simply an hack to trigger the collision detection and bullet pointer reset on all the
     * bullets fired by all the turrets, the time set to 0 let the bullets remain in the same position while the remaining
     * code is executed as desired.
     */
    for(const sptr<Turret>& turret : turrets) {
        turret->moveBullets(0, enemies);
    }
}

void TurretGenerator::notifyMovementToTurrets(sptr<Enemy>& enemy, int elapsed_time) {
    for(const sptr<Turret>& turret : turrets) {
        turret->notify(enemy, elapsed_time);
    }
}
