//
// Created by ebalo on 21/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_STARTBUTTONHOVER_H
#define TD_TOWERDEFENSE_SFML_STARTBUTTONHOVER_H

#include "../Interface/Event.h"
#include "../Elements/ButtonRect.h"

class StartButtonHoverEvent :public Event {
private:
    ButtonRect *btn;
    sf::Color hover;
    bool method;
public:
    StartButtonHoverEvent(ButtonRect *btn, bool hover = true) :Event(btn), btn(btn), method(hover) {}

    void callback() {
        if(method) {
            hover = btn->getColor();
            btn->setColor(hover, true);
            btn->setLabelColor(sf::Color(0xcc, 0xcc, 0xcc));
        }
        else {
            hover = btn->getColor();
            hover.a = 0;
            btn->setColor(hover, true);
            btn->setLabelColor(sf::Color(0, 0, 0));
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_STARTBUTTONHOVER_H
