//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_TURRETGENERATOR_H
#define TD_TOWERDEFENSE_TURRETGENERATOR_H

#include <vector>
#include <unordered_map>
#include <map>
#include <forward_list>
#include "Turret.h"
#include "../States/TurretState.h"
#include "ButtonIcon.h"
#include "../EventHandler.h"
#include "../Maps/Map.h"
#include "ButtonRect.h"
#include "../Observers/MouseHoverObserver.h"
#include "../Events/IconButtonHover.h"
#include "../Observers/MouseOutObserver.h"
#include "../Observers/MouseClickObserver.h"
#include "../Maps/RenderableMap.h"

class TurretGenerator : public sf::Drawable, public sf::Transformable, public Notifier, public RenderableMap {
private:
    std::vector<Turret *> initialized_instances;
    std::forward_list<Turret *> *turrets;
    std::map<int, int> initialized_instances_map;

    int selected_turret;
    Button *craft_virtual_button;

    bool menu_first_page = true,
        turret_placing_loop = false;

    Map *map;
    bool is_map_easy = false;

    sf::RenderWindow *window;
    sf::Font *font;

    EventHandler *eventHandler;

    void generateInstancesMap();

    void renderTurretMenu(sf::RenderTarget& target, sf::RenderStates states) const;
    void renderTurretAvailableLocations(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    TurretGenerator(sf::RenderWindow *window, sf::Font *font, EventHandler *eventHandler, Map *map, bool is_map_easy, std::forward_list<Turret *> *turrets, std::vector<Turret *> initialized_instances);

    TurretGenerator *selectTurret(TURRET_TYPE turret);
    void switchMenuPage();
    void setTurretPlacement(bool state);
    Turret *generate(int turret_index);

    sf::Font *getFont();
    Map *getMap();
    int getSelectedTurret();
    EventHandler *getEventHandler();
    sf::Sprite *cloneTurretSprite(int index);
    void destroyCraftedTurretSprite();

    void setCraftVirtualButton(Button *btn);
};


#endif //TD_TOWERDEFENSE_TURRETGENERATOR_H
