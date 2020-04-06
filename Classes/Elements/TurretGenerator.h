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
#include "DrawableFactory.h"

class TurretGenerator : public sf::Drawable, public sf::Transformable, public Notifier, public RenderableMap {
private:
    std::vector<Turret *> initialized_instances;
    std::map<int, int> initialized_instances_map;
    std::vector<Turret *> turrets;

    bool menu_first_page = true,
            turret_placing_loop = false;
    int selected_turret;

    Button *craft_virtual_button;
    Map *map;
    EventHandler *eventHandler;
    DrawableFactory factory;

    sf::RenderWindow *window;
    sf::Font *font;

    void generateInstancesMap();

    void renderTurretMenu(sf::RenderTarget& target, sf::RenderStates states) const;
    void renderTurretAvailableLocations(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    TurretGenerator(sf::RenderWindow *window, sf::Font *font, EventHandler *eventHandler, Map *map, bool is_easy, Tower *tower, sf::Texture *texture);

    Turret *generate(int turret_index);
    TurretGenerator *selectTurret(TURRET_TYPE turret);

    void switchMenuPage();
    void setTurretPlacement(bool state);
    sf::Sprite *cloneTurretSprite(int index);
    void destroyCraftedTurretSprite();
    void setCraftVirtualButton(Button *btn);

    sf::Font *getFont();
    Map *getMap();
    int getSelectedTurret();
    EventHandler *getEventHandler();

    void registerTurret(Turret *turret);
    std::vector<Turret *> *getRegisteredTurrets();
};


#endif //TD_TOWERDEFENSE_TURRETGENERATOR_H
