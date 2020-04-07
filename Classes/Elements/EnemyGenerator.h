//
// Created by ebalo on 23/03/20.
//

#ifndef TD_TOWERDEFENSE_ENEMYGENERATOR_H
#define TD_TOWERDEFENSE_ENEMYGENERATOR_H

#include <memory>
#include <vector>
#include <forward_list>
#include <map>
#include "../States/GameState.h"
#include "../States/EnemyState.h"
#include "Enemy.h"
#include "Tower.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class EnemyGenerator : public Notifier {
private:
    std::map<ENEMY_TYPE, size_t> enemies_generation_timer;

    struct generativeConstructor {
        size_t time_since_round,
            total_elapsed_time,
            max_running_time,
            generation_delay;
        bool started;
        int already_generated,
            upper_bound;
    };

    /**
     * Elapsed time will have a struct like:
     *  { 123456789, generativeConstructor { 1.25, false } }
     * In order they represent:
     *      - Hash code of the class whose generation is associated to
     *      * generativeConstructor
     *      - A double indicating the time elapsed since last generation
     *      - A double indicating the total time elapsed since generation start
     *      - A double indicating the maximum generation time
     *          *NOTE:* this can be deactivated by the assigment of 0
     *      - A true/false flag indicating whether the generation process is started or not
     *      - An integer representing the number of element already generated
     *      - An integer representing the maximum number of element to generate
     *          *NOTE:* this can be deactivated by the assigment of -1
     * In order to construct a structure like th
     */
    std::map<ENEMY_TYPE, sptr<generativeConstructor>> generative_map;

    sptr<std::forward_list<sptr<Enemy>>> enemies;
    std::vector<std::shared_ptr<Enemy>> initialized_instances;
    std::map<ENEMY_TYPE, int> initialized_instances_map;

    std::vector<sptr<Enemy>> to_remove;

    Tower *tower;

    void triggerGeneration(double time_elapsed);
    void generateInstancesMap();
public:
    /**
     * Construct the enemy generator instance.
     * @param difficult
     * @param enemies Pointer to the RendererHandler instance of enemies
     * @param initialized_instances MUST contain all the enemy and bosses instances, ALREADY INITIALIZED to their default values, following generation will clone these instances
     */
    EnemyGenerator(GAME_STATE difficult, sptr<std::forward_list<sptr<Enemy>>> enemies, Tower *tower, std::vector<sptr<Map>> maps, bool game_type, sf::Texture *texture);

    void genFixedNumber(ENEMY_TYPE type, int amount = 1, size_t delay = 0);
    void genForTime(ENEMY_TYPE type, size_t total_generation_time_millis, size_t delay = 0);

    void tick(double time);

    void markEnemyAsToRemove(sptr<Enemy> enemy);
    void syncEnemies();
};


#endif //TD_TOWERDEFENSE_ENEMYGENERATOR_H
