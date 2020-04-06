//
// Created by ebalo on 02/04/20.
//

#include "Bullet.h"

Bullet::Bullet(int vx, int vy, int power, sf::Vector2f origin) :vx(vx), vy(vy), power(power) {
    bullet.setRadius(4);
    bullet.setFillColor(sf::Color {0, 0, 0 });
    bullet.setOrigin(2.5, 2.5);
    bullet.setPosition(origin);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(bullet, states);
}

void Bullet::move(int time_lapse) {
    bullet.move(sf::Vector2f {(float)(vx * time_lapse /1000), (float)(vy * time_lapse /1000)});
    sf::Vector2f pos = bullet.getPosition();
    if(pos.x >= WINDOW_WIDTH || pos.x <= 0 || pos.y >= WINDOW_HEIGHT || pos.y <= 0) {
        delete this;
    }
}
