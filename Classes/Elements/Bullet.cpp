//
// Created by ebalo on 02/04/20.
//

#include "Bullet.h"

Bullet::Bullet(int velocity, int acceleration, int power, Enemy *victim, sf::Vector2f origin) :velocity(velocity), acceleration(acceleration), power(power), victim(victim) {
    bullet.setRadius(10);
    bullet.setFillColor(sf::Color {0, 0, 0 });
    bullet.setOrigin(5, 5);
    bullet.setPosition(origin);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(bullet, states);
}

void Bullet::move(int time_lapse) {

}
