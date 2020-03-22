//
// Created by ebalo on 22/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_DIFFICULTBUTTONHOVER_H
#define TD_TOWERDEFENSE_SFML_DIFFICULTBUTTONHOVER_H

#include "../Interface/Event.h"
#include "../Elements/ButtonRect.h"

class DifficultButtonHoverEvent :public Event {
private:
    ButtonRect *btn;
    sf::Color hover,
        label;
    bool method;
public:
    DifficultButtonHoverEvent(ButtonRect *btn, bool hover = true, sf::Color label = sf::Color(0, 0, 0)) :Event(btn), btn(btn), method(hover), label(label) {}

    void callback() {
        if(method) {
            hover = btn->getColor();
            btn->setColor(hover, true);
            btn->setLabelColor(label);
        }
        else {
            hover = btn->getColor();
            hover.a = 0;
            btn->setColor(hover, true);
            btn->setLabelColor(label);
        }
    }
};

#endif //TD_TOWERDEFENSE_SFML_DIFFICULTBUTTONHOVER_H
