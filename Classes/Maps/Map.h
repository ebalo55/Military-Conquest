//
// Created by ebalo on 20/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_MAP_H
#define TD_TOWERDEFENSE_SFML_MAP_H
#include <SFML/Graphics.hpp>
#include <exception>
#include "AssetsMap.h"

/* Maps code:
 *      - 0 -> Path
 *      - 1 -> Terrain
 *      - 2 -> Tree
 *      - 3 -> Rock
 *      - 4 -> Turret placement overlay
 *      - 5 -> Turret 1
 *      - 6 -> Turret 2
 *      - 7 -> Turret 3
 *      - 8 -> Turret 4
 *      - 9 -> Turret 5
 */
class Map : public sf::Drawable, public sf::Transformable, public std::exception {
protected:
    int *map,
        map_width = 32,
        map_height = 20;
    sf::VertexArray vertices;
    sf::Texture texture;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();         // apply the transform
        states.texture = &texture;                  // apply the tiles texture
        target.draw(vertices, states);              // draw the vertex array
    }
public:
    Map() {};
    void generate(sf::Vector2u tileSize, const int* tiles, int width, int height, bool turret_placement_mode = false) noexcept(false) {
        // load the tiles texture
        if(!texture.loadFromFile(AssetsMap::get("tile-set"))) {
            throw std::runtime_error(AssetsMap::get("tile-set") + " not found.");
        }

        // resize the vertex array to fit the level size
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(width * height * 4);    // rgba

        // populate the vertex array, with one quad per tile
        int tile_number, tile, tu, tv;
        
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {

                // get the current tile number
                tile = tiles[i + j * width];
                tile_number = !turret_placement_mode && tile == 4 ? 1 : tile;

                // find its position in the tileset texture
                tu = tile_number % (texture.getSize().x / tileSize.x);
                tv = tile_number / (texture.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex *quad = &vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
    }

    int *getMap() { return map; }
    int getMapWidth() { return map_width; }
    int getMapHeight() { return map_height; }
};


#endif //TD_TOWERDEFENSE_SFML_MAP_H
