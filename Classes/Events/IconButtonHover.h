//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_SFML_ICONBUTTONHOVER_H
#define TD_TOWERDEFENSE_SFML_ICONBUTTONHOVER_H

#include "../Interface/Event.h"
#include "../Elements/ButtonIcon.h"

class IconButtonHoverEvent :public Event {
private:
    std::shared_ptr<ButtonIcon> btn;
    bool method;
public:
    IconButtonHoverEvent(std::shared_ptr<ButtonIcon> btn, bool hover = true) :Event(btn), btn(btn), method(hover) {}

    void callback() { }
};

#endif //TD_TOWERDEFENSE_SFML_ICONBUTTONHOVER_H
