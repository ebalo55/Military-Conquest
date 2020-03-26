//
// Created by ebalo on 24/03/20.
//

#include "TurretGenerator.h"
#include "../Events/TurretMenuButtonClick.h"
#include "../Events/DifficultButtonHover.h"
#include "../Events/CraftTurretButtonClick.h"

TurretGenerator::TurretGenerator(sf::RenderWindow *window, sf::Font *font, EventHandler *eventHandler, Map *map, bool is_map_easy, std::forward_list<Turret *> *turrets, std::vector<Turret *> initialized_instances) {
    this->window = window;
    this->turrets = turrets;
    this->initialized_instances = std::move(initialized_instances);
    this->font = font;
    this->eventHandler = eventHandler;
    this->is_map_easy = is_map_easy;
    this->map = map;

    sf::Texture *texture = initTexture("right-arrow");
    texture->loadFromFile(AssetsMap::get("right-arrow"));
    ButtonIcon *button_icon = initButtonIcon("right-arrow");
    button_icon->setTexture(texture);
    button_icon->setPosition(WINDOW_WIDTH -20, WINDOW_HEIGHT -20);
    eventHandler->registerButton(button_icon);
    new MouseHoverObserver(button_icon, new IconButtonHoverEvent(button_icon), window);
    new MouseOutObserver(button_icon, new IconButtonHoverEvent(button_icon, false), window);
    new MouseClickObserver(button_icon, new TurretMenuButtonClickEvent(button_icon, this), window);

    texture = initTexture("left-arrow");
    texture->loadFromFile(AssetsMap::get("left-arrow"));
    button_icon = initButtonIcon("left-arrow");
    button_icon->setTexture(texture);
    button_icon->setPosition(WINDOW_WIDTH -20, WINDOW_HEIGHT -20);
    new MouseHoverObserver(button_icon, new IconButtonHoverEvent(button_icon), window);
    new MouseOutObserver(button_icon, new IconButtonHoverEvent(button_icon, false), window);
    new MouseClickObserver(button_icon, new TurretMenuButtonClickEvent(button_icon, this), window);

    texture = initTexture("craft");
    texture->loadFromFile(AssetsMap::get("craft"));

    texture = initTexture("craft-close");
    texture->loadFromFile(AssetsMap::get("craft-close"));

    rect.setPosition(sf::Vector2f {WINDOW_WIDTH - 200, WINDOW_HEIGHT - 310});
    rect.setSize(sf::Vector2f {200, 310});
    rect.setFillColor(sf::Color(0, 0, 0, 0xaa));

    generateInstancesMap();
}

Turret *TurretGenerator::generate(int turret_index) {
    return new Turret(initialized_instances[turret_index]);
    //turret_map->setTurret(initialized_instances[initialized_instances_map[selected_turret]], nearest_grid_block);
}

void TurretGenerator::generateInstancesMap() {
    sf::Sprite *sprite;
    sf::Text *text;
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
        sprite->setPosition(sf::Vector2f {WINDOW_WIDTH - 195, (float)(WINDOW_HEIGHT - (5 + positional_factor))});

        text = initText(turret->getTurretName());
        text->setFont(*font);
        text->setString(turret->getTurretName());
        text->setCharacterSize(15);
        text->setFillColor(color);
        text->setStyle(sf::Text::Style::Bold);
        text->setPosition(sf::Vector2f {WINDOW_WIDTH - 150, (float)(WINDOW_HEIGHT - (5 + positional_factor))});

        text = initText(turret->getTurretName() + "-radius");
        text->setFont(*font);
        stringstream.str("");
        stringstream << "Radius: " << turret->getRadius();
        text->setString(stringstream.str());
        text->setCharacterSize(12);
        text->setFillColor(color);
        text->setPosition(sf::Vector2f {WINDOW_WIDTH - 150, (float)(WINDOW_HEIGHT - (-25 + positional_factor))});

        text = initText(turret->getTurretName() + "-power");
        text->setFont(*font);
        stringstream.str("");
        stringstream << "Power: " << turret->getPower();
        text->setString(stringstream.str());
        text->setCharacterSize(12);
        text->setFillColor(color);
        text->setPosition(sf::Vector2f {WINDOW_WIDTH - 190, (float)(WINDOW_HEIGHT - (-40 + positional_factor))});

        text = initText(turret->getTurretName() + "-fire-rate");
        text->setFont(*font);
        stringstream.str("");
        stringstream << "Fire rate: " << turret->getFireRate() << " shots/s";
        text->setString(stringstream.str());
        text->setCharacterSize(12);
        text->setFillColor(color);
        text->setPosition(sf::Vector2f {WINDOW_WIDTH - 190, (float)(WINDOW_HEIGHT - (-55 + positional_factor))});

        text = initText(turret->getTurretName() + "-cost");
        text->setFont(*font);
        stringstream.str("");
        stringstream << "Cost: " << turret->getCost();
        text->setString(stringstream.str());
        text->setCharacterSize(12);
        text->setFillColor(color);
        text->setPosition(sf::Vector2f {WINDOW_WIDTH - 190, (float)(WINDOW_HEIGHT - (-70 + positional_factor))});

        button = initButtonRect(turret->getTurretName() + "-craft");
        button->setSize(30, 30);
        button->setColor(sf::Color(0x40, 0xb8, 0x68));
        button->setPosition(WINDOW_WIDTH - 40, WINDOW_HEIGHT - (-35 + positional_factor));
        new MouseHoverObserver(button, new DifficultButtonHoverEvent(button), window);
        new MouseOutObserver(button, new DifficultButtonHoverEvent(button, false), window);
        new MouseClickObserver(button, new CraftTurretButtonClickEvent(button, window, this, x), window);
        sprite = initSprite(turret->getTurretName() + "-craft");
        sprite->setPosition(sf::Vector2f {WINDOW_WIDTH - 35, (float)(WINDOW_HEIGHT - (-40 + positional_factor))});
        sprite->setTexture(*getTexture("craft"));
        sprite = initSprite(turret->getTurretName() + "-craft-close");
        sprite->setPosition(sf::Vector2f {WINDOW_WIDTH - 35, (float)(WINDOW_HEIGHT - (-40 + positional_factor))});
        sprite->setTexture(*getTexture("craft-close"));

        if(x < 3) { eventHandler->registerButton(button); }

        x++;
    }
}

void TurretGenerator::renderTurretMenu(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect, states);

    std::string name;
    for(int i = (menu_first_page ? 0 : 3); i < (menu_first_page ? 3 : 5); i++) {
        name = initialized_instances[i]->getTurretName();
        target.draw(*initialized_instances[i]->getSprite(), states);

        target.draw(*getText(name), states);
        target.draw(*getText(name + "-radius"), states);
        target.draw(*getText(name + "-power"), states);
        target.draw(*getText(name + "-fire-rate"), states);
        target.draw(*getText(name + "-cost"), states);
        target.draw(rect_buttons_map.at(name + "-craft"), states);
        if(!turret_placing_loop || selected_turret != i) {
            target.draw(sprites_map.at(name + "-craft"), states);
        }
        else if(turret_placing_loop && selected_turret == i) {
            target.draw(sprites_map.at(name + "-craft-close"), states);
        }
    }

    if(sprites_map.find("craft_turret_sprite") != sprites_map.end()) {
        sf::Sprite sprite = sprites_map.at("craft_turret_sprite");
        target.draw(sprite);
    }

    target.draw(menu_first_page ? *getButtonIcon("right-arrow") : *getButtonIcon("left-arrow"), states);
}

void TurretGenerator::renderTurretAvailableLocations(sf::RenderTarget& target, sf::RenderStates states) const {
    map->generate(sf::Vector2u(40, 40), map->getMap(), map->getMapWidth(), map->getMapHeight(), true);
}

TurretGenerator *TurretGenerator::selectTurret(TURRET_TYPE turret) {
    selected_turret = turret == ::turret1 ? turret1 : turret == ::turret2 ? turret2 : turret == ::turret3 ? turret3 : turret == ::turret4 ? turret4 : turret5;
    return this;
}

sf::Sprite *TurretGenerator::initSprite(const std::string& name) {
    sprites_map[name] = sf::Sprite();
    return &sprites_map[name];
}

sf::Sprite *TurretGenerator::getSprite(const std::string& name) {
    return &sprites_map[name];
}

sf::Texture *TurretGenerator::initTexture(const std::string& name) {
    textures_map[name] = sf::Texture();
    return &textures_map[name];
}

sf::Texture *TurretGenerator::getTexture(const std::string& name) {
    return &textures_map[name];
}

ButtonRect *TurretGenerator::initButtonRect(const std::string& name) {
    rect_buttons_map[name] = ButtonRect();
    return &rect_buttons_map[name];
}

ButtonRect *TurretGenerator::getButtonRect(const std::string& name) {
    return &rect_buttons_map[name];
}

sf::Text *TurretGenerator::initText(const std::string &name) {
    texts_map[name] = sf::Text();
    return &texts_map[name];
}

const sf::Text * TurretGenerator::getText(const std::string &name) const {
    return &texts_map.at(name);
}

ButtonIcon *TurretGenerator::initButtonIcon(const std::string &name) {
    icon_buttons_map[name] = ButtonIcon();
    return &icon_buttons_map[name];
}

const ButtonIcon *TurretGenerator::getButtonIcon(const std::string &name) const {
    return &icon_buttons_map.at(name);
}

void TurretGenerator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(std::pair<std::string, sf::Drawable *> line : turrets_datas) {
        target.draw(*line.second);
    }

    renderTurretMenu(target, states);
    if(turret_placing_loop) { renderTurretAvailableLocations(target, states); }

}

void TurretGenerator::switchMenuPage() {
    menu_first_page = !menu_first_page;
    if(menu_first_page) {
        for(int i = 0; i < 5; i++) {
            if(i >= 3) { eventHandler->deleteButton(&rect_buttons_map[initialized_instances[i]->getTurretName() + "-craft"]); }
            else { eventHandler->registerButton(&rect_buttons_map[initialized_instances[i]->getTurretName() + "-craft"]); }
        }
        eventHandler->deleteButton(&icon_buttons_map["left-arrow"]);
        eventHandler->registerButton(&icon_buttons_map["right-arrow"]);
    }
    else {
        for(int i = 0; i < 5; i++) {
            if(i < 3) { eventHandler->deleteButton(&rect_buttons_map[initialized_instances[i]->getTurretName() + "-craft"]); }
            else { eventHandler->registerButton(&rect_buttons_map[initialized_instances[i]->getTurretName() + "-craft"]); }
        }
        eventHandler->deleteButton(&icon_buttons_map["right-arrow"]);
        eventHandler->registerButton(&icon_buttons_map["left-arrow"]);
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

    Turret *instance = initialized_instances[index];
    sf::Sprite *craft_turret_sprite = initSprite("craft_turret_sprite");
    craft_turret_sprite->setTexture(*instance->getSprite()->getTexture());
    craft_turret_sprite->setTextureRect(sf::IntRect {(5 + index) *40, 0, 40, 40});

    return craft_turret_sprite;
}

void TurretGenerator::destroyCraftedTurretSprite() {
    if(sprites_map.find("craft_turret_sprite") != sprites_map.end()) {
        sprites_map.erase("craft_turret_sprite");
        eventHandler->addToRemoveList(craft_virtual_button);
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

void TurretGenerator::registerTurretData(const std::string& name, sf::Drawable *drawable, bool if_absent) {
    if(if_absent) {
        if(turrets_datas.find(name) == turrets_datas.end()) {
            turrets_datas[name] = drawable;
        }
    }
    else { turrets_datas[name] = drawable; }
}

void TurretGenerator::deleteTurretData(const std::string& name) {
    auto position = turrets_datas.find(name);
    if(position != turrets_datas.end()) {
        turrets_datas.erase(position);
    }
}
