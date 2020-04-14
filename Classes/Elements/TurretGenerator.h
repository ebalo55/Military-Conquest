//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_TURRETGENERATOR_H
#define TD_TOWERDEFENSE_TURRETGENERATOR_H

#include <vector>
#include <unordered_map>
#include <map>
#include <forward_list>
#include <memory>
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

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class TurretGenerator : public sf::Drawable, public sf::Transformable, public Notifier, public RenderableMap {
private:
    std::vector<sptr<Turret>> initialized_instances;
    std::map<int, int> initialized_instances_map;
    std::vector<sptr<Turret>> turrets;

    bool menu_first_page = true,
            turret_placing_loop = false;
    int selected_turret;

    sptr<Button> craft_virtual_button;
    sptr<Map> map;
    sptr<EventHandler> eventHandler;
    sptr<DrawableFactory> factory;

    sptr<sf::RenderWindow> window;
    sptr<sf::Font> font;

    void generateInstancesMap();

    void renderTurretMenu(sf::RenderTarget& target, sf::RenderStates states) const;
    void renderTurretAvailableLocations(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    TurretGenerator(const sptr<sf::RenderWindow>& window, sptr<sf::Font> font, const sptr<EventHandler>& eventHandler, sptr<Map> map, bool is_easy, const sptr<Tower>& tower);

    sptr<Turret> generate(int turret_index);
    void selectTurret(TURRET_TYPE turret);

    void switchMenuPage();
    void setTurretPlacement(bool state);
    sptr<sf::Sprite> cloneTurretSprite(int index);
    void destroyCraftedTurretSprite();
    void setCraftVirtualButton(sptr<Button> btn);

    sptr<sf::Font> getFont();
    Map *getMap();
    int getSelectedTurret();
    sptr<EventHandler> getEventHandler();

    void registerTurret(const sptr<Turret>& turret);
    sptr<std::vector<sptr<Turret>>> getRegisteredTurrets();

    std::vector<sptr<Bullet>> getBullets();

    // TODO: Move the following function into an adapter and extend it as a class
    void moveBullets(int elapsed_time, const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies);
    void triggerBulletCollisionDetection(const sptr<std::map<unsigned long long, sptr<Enemy>>>& enemies);
    void notifyMovementToTurrets(const sptr<Enemy>& enemy, int elapsed_time);
};


#endif //TD_TOWERDEFENSE_TURRETGENERATOR_H
