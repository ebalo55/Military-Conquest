//
// Created by ebalo on 20/03/20.
//

#include <iostream>
#include "EventHandler.h"

EventHandler::EventHandler(sf::RenderWindow *window, GAME_STATE *state) :window(window), state(state) {

}

void EventHandler::handle() {
    queueWorker();

    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) { window->close(); }
        else if(event.type == sf::Event::MouseMoved) {
            notifyButtons(OBSERVERS_TYPE_ID::mouse_motion);
        }
        else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            notifyButtons(OBSERVERS_TYPE_ID::mouse_click_left);
        }
        else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
            notifyButtons(OBSERVERS_TYPE_ID::mouse_click_right);
            std::cout << "Mouse right click received" << std::endl;
        }
    }
}

GAME_STATE *EventHandler::getGameState() {
    return state;
}

sf::RenderWindow *EventHandler::getRenderWindow() {
    return window;
}

void EventHandler::registerButton(Button *btn) {
    buttons.push_back(btn);
}

void EventHandler::deleteButton(Button *btn) {
    buttons.remove(btn);
    delete btn;
}

void EventHandler::hideButton(Button *btn) {
    buttons.remove(btn);
}

void EventHandler::notifyButtons(OBSERVERS_TYPE_ID ev_code) {
    for(Button *btn : buttons) {
        btn->notify(ev_code);
    }
}

void EventHandler::addToRemoveList(Button *btn) {
    queue.emplace_back(QueueOpCode::remove, btn);
}

void EventHandler::addToList(Button *btn) {
    queue.emplace_back(QueueOpCode::add, btn);
}

void EventHandler::addToHideList(Button *btn) {
    queue.emplace_back(QueueOpCode::hide, btn);
}

void EventHandler::queueWorker() {
    for(std::pair<QueueOpCode, Button *> line : queue) {
        switch(line.first) {
            case add:
                registerButton(line.second);
                break;
            case remove:
                deleteButton(line.second);
                break;
            case hide:
                hideButton(line.second);
                break;
        }
    }
    queue.clear();
}
