//
// Created by ebalo on 24/03/20.
//

#include "TurretGenerator.h"
#include "../Events/TurretMenuButtonClick.h"
#include "../Events/DifficultButtonHover.h"
#include "../Events/CraftTurretButtonClick.h"

TurretGenerator::TurretGenerator(sf::RenderWindow *window, sf::Font *font, EventHandler *eventHandler, Map *map, std::vector<Turret *> initialized_instances) {
    factory.setEventHandler(eventHandler);
    factory.setWindow(window);

    this->window = window;
    this->initialized_instances = std::move(initialized_instances);
    this->font = font;
    this->eventHandler = eventHandler;
    this->map = map;

    factory.instantiateTexture("right-arrow", AssetsMap::get("right-arrow"));
    factory.instantiateTexture("left-arrow", AssetsMap::get("left-arrow"));

    ButtonIcon *button_icon = factory.instantiateButtonIcon("right-arrow", "right-arrow", sf::Vector2f {WINDOW_WIDTH -20, WINDOW_HEIGHT -20});
    factory.linkEvent(button_icon,
            new IconButtonHoverEvent(button_icon),
            new IconButtonHoverEvent(button_icon, false),
            new TurretMenuButtonClickEvent(button_icon, this));

    button_icon = factory.instantiateButtonIcon("left-arrow", "left-arrow", sf::Vector2f {WINDOW_WIDTH -20, WINDOW_HEIGHT -20});
    factory.linkEvent(button_icon,
            new IconButtonHoverEvent(button_icon),
            new IconButtonHoverEvent(button_icon, false),
            new TurretMenuButtonClickEvent(button_icon, this));

    factory.instantiateTexture("craft", AssetsMap::get("craft"));
    factory.instantiateTexture("craft-close", AssetsMap::get("craft-close"));
    factory.instantiateTexture("hud-bg", AssetsMap::get("vertical-hud-bg"));
    factory.instantiateSprite("hud-bg", "hud-bg", sf::Vector2f {WINDOW_WIDTH - 200, WINDOW_HEIGHT - 310});

    generateInstancesMap();
}

Turret *TurretGenerator::generate(int turret_index) {
    return new Turret(initialized_instances[turret_index]);
}

void TurretGenerator::generateInstancesMap() {
    sf::Sprite *sprite;
    ButtonRect *button;
    sf::Color color(0xdd, 0xdd, 0xdd);
    std::stringstream stringstream;

    int x = 0,
        positional_factor;
    for(Turret *turret : initialized_instances) {
        int hashcode = turret->getHashCode();
        if(hashcode == turret1) { initialized_instances_map[turret1] = x; }
        else if(hashcode == turret2) { initialized_instances_map[turret2] = x; }
        else if(hashcode == turret3) { initialized_instances_map[turret3] = x; }
        else if(hashcode == turret4) { initialized_instances_map[turret4] = x; }
        else if(hashcode == turret5) { initialized_instances_map[turret5] = x; }

        positional_factor = (3 - hashcode % 3) * 100;

        sprite = turret->getSprite();
        sprite->setPosition(sf::Vector2f {WINDOW_WIDTH - 185, (float)(WINDOW_HEIGHT - (-5 + positional_factor))});

        factory.instantiateText(turret->getTurretName(),
                font,
                turret->getTurretName(),
                sf::Vector2f {WINDOW_WIDTH - 140, (float)(WINDOW_HEIGHT - (-5 + positional_factor))},
                15,
                color,
                sf::Text::Style::Bold);

        stringstream.str("");
        stringstream << "Radius: " << turret->getRadius();
        factory.instantiateText(turret->getTurretName() + "-radius",
                font,
                stringstream.str(),
                sf::Vector2f {WINDOW_WIDTH - 140, (float)(WINDOW_HEIGHT - (-35 + positional_factor))},
                12,
                color);

        stringstream.str("");
        stringstream << "Power: " << turret->getPower();
        factory.instantiateText(turret->getTurretName() + "-power",
                font,
                stringstream.str(),
                sf::Vector2f {WINDOW_WIDTH - 175, (float)(WINDOW_HEIGHT - (-50 + positional_factor))},
                12,
                color);

        stringstream.str("");
        stringstream << "Fire rate: " << turret->getFireRate() << " shots/s";
        factory.instantiateText(turret->getTurretName() + "-fire-rate",
                font,
                stringstream.str(),
                sf::Vector2f {WINDOW_WIDTH - 175, (float)(WINDOW_HEIGHT - (-65 + positional_factor))},
                12,
                color);

        stringstream.str("");
        stringstream << "Cost: " << turret->getCost();
        factory.instantiateText(turret->getTurretName() + "-cost",
                font,
                stringstream.str(),
                sf::Vector2f {WINDOW_WIDTH - 175, (float)(WINDOW_HEIGHT - (-80 + positional_factor))},
                12,
                color);

        button = factory.instantiateButtonRect(turret->getTurretName() + "-craft",
                sf::Vector2i {30, 30},
                font,
                "",
                0,
                sf::Color(0x40, 0xb8, 0x68),
                sf::Color(0, 0, 0),
                sf::Vector2f {WINDOW_WIDTH - 40, (float)(WINDOW_HEIGHT - (-35 + positional_factor))});
        new MouseHoverObserver(button, new DifficultButtonHoverEvent(button), window);
        new MouseOutObserver(button, new DifficultButtonHoverEvent(button, false), window);
        new MouseClickObserver(button, new CraftTurretButtonClickEvent(button, window, this, x), window);

        factory.instantiateSprite(turret->getTurretName() + "-craft", "craft", sf::Vector2f {WINDOW_WIDTH - 35, (float)(WINDOW_HEIGHT - (-40 + positional_factor))});
        factory.instantiateSprite(turret->getTurretName() + "-craft-close", "craft-close", sf::Vector2f {WINDOW_WIDTH - 35, (float)(WINDOW_HEIGHT - (-40 + positional_factor))});

        if(x < 3) { eventHandler->registerButton(button); }
        x++;
    }
}

void TurretGenerator::renderTurretMenu(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*factory.getSprite("hud-bg"), states);

    std::string name;
    for(int i = (menu_first_page ? 0 : 3); i < (menu_first_page ? 3 : 5); i++) {
        name = initialized_instances[i]->getTurretName();
        target.draw(*initialized_instances[i]->getSprite(), states);

        for(std::string str : {"", "-radius", "-power", "-fire-rate", "-cost"}) {
            target.draw(*factory.getText(name + str), states);
        }
        target.draw(*factory.getButtonRect(name + "-craft"), states);

        if(!turret_placing_loop || selected_turret != i) {
            target.draw(*factory.getSprite(name + "-craft"), states);
        }
        else if(turret_placing_loop && selected_turret == i) {
            target.draw(*factory.getSprite(name + "-craft-close"), states);
        }
    }

    if(factory.has(DrawableFactory::Maps::sprites, "craft_turret_sprite")) {
        target.draw(*factory.getSprite("craft_turret_sprite"));
    }

    target.draw(menu_first_page ? *factory.getButtonIcon("right-arrow") : *factory.getButtonIcon("left-arrow"), states);
}

void TurretGenerator::renderTurretAvailableLocations(sf::RenderTarget& target, sf::RenderStates states) const {
    map->generate(sf::Vector2u(40, 40), map->getMap(), map->getMapWidth(), map->getMapHeight(), true);
}

TurretGenerator *TurretGenerator::selectTurret(TURRET_TYPE turret) {
    selected_turret = turret == ::turret1 ? turret1 : turret == ::turret2 ? turret2 : turret == ::turret3 ? turret3 : turret == ::turret4 ? turret4 : turret5;
    return this;
}

void TurretGenerator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(std::pair<std::string, sf::Drawable *> line : drawable_map) {
        target.draw(*line.second);
    }

    renderTurretMenu(target, states);
    if(turret_placing_loop) { renderTurretAvailableLocations(target, states); }

}

void TurretGenerator::switchMenuPage() {
    menu_first_page = !menu_first_page;
    if(menu_first_page) {
        factory.unlinkButton({
            initialized_instances[0]->getTurretName() + "-craft",
            initialized_instances[1]->getTurretName() + "-craft",
            initialized_instances[2]->getTurretName() + "-craft",
            "left-arrow"
        });
        factory.linkButton({
            initialized_instances[3]->getTurretName() + "-craft",
            initialized_instances[4]->getTurretName() + "-craft",
            "right-arrow"
        });
    }
    else {
        factory.linkButton({
            initialized_instances[0]->getTurretName() + "-craft",
            initialized_instances[1]->getTurretName() + "-craft",
            initialized_instances[2]->getTurretName() + "-craft",
            "left-arrow"
        });
        factory.unlinkButton({
            initialized_instances[3]->getTurretName() + "-craft",
            initialized_instances[4]->getTurretName() + "-craft",
            "right-arrow"
        });
    }
}

void TurretGenerator::setTurretPlacement(bool state) {
    turret_placing_loop = state;
    if(!turret_placing_loop) { map->generate(sf::Vector2u(40, 40), map->getMap(), map->getMapWidth(), map->getMapHeight()); }
}

EventHandler *TurretGenerator::getEventHandler() {
    return eventHandler;
}

sf::Sprite *TurretGenerator::cloneTurretSprite(int index) {
    destroyCraftedTurretSprite();
    selected_turret = index;

    return factory.instantiateSprite("craft_turret_sprite",
            initialized_instances[index]->getSprite()->getTexture(),
            (sf::Vector2f)sf::Mouse::getPosition(),
            sf::IntRect {(5 + index) *40, 0, 40, 40});
}

void TurretGenerator::destroyCraftedTurretSprite() {
    if(factory.has(DrawableFactory::Maps::sprites, "craft_turret_sprite")) {
        factory.clear(DrawableFactory::Maps::sprites, {"craft_turret_sprite"});
        factory.unlinkButton(craft_virtual_button);
    }
}

void TurretGenerator::setCraftVirtualButton(Button *btn) {
    craft_virtual_button = btn;
}

Map *TurretGenerator::getMap() {
    return map;
}

int TurretGenerator::getSelectedTurret() {
    return selected_turret;
}

sf::Font *TurretGenerator::getFont() {
    return font;
}
