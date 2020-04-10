//
// Created by ebalo on 20/03/20.
//

#include <iostream>
#include "EventHandler.h"

EventHandler::EventHandler(sptr<sf::RenderWindow> window, sptr<GAME_STATE> state) :window(window), state(state) {}

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

std::shared_ptr<GAME_STATE> EventHandler::getGameState() {
    return state;
}

std::shared_ptr<sf::RenderWindow> EventHandler::getRenderWindow() {
    return window;
}

void EventHandler::registerButton(sptr<Button> btn) {
    buttons.push_back(btn);
}

void EventHandler::deleteButton(sptr<Button> btn) {
    buttons.remove(btn);
    btn.reset();
}

void EventHandler::hideButton(sptr<Button> btn) {
    buttons.remove(btn);
}

void EventHandler::notifyButtons(OBSERVERS_TYPE_ID ev_code) {
    for(sptr<Button> btn : buttons) {
        btn->notify(ev_code);
    }
}

void EventHandler::addToRemoveList(sptr<Button> btn) {
    queue.emplace_back(QueueOpCode::remove, btn);
}

void EventHandler::addToList(sptr<Button> btn) {
    queue.emplace_back(QueueOpCode::add, btn);
}

void EventHandler::addToHideList(sptr<Button> btn) {
    queue.emplace_back(QueueOpCode::hide, btn);
}

void EventHandler::queueWorker() {
    for(std::pair<QueueOpCode, sptr<Button>> line : queue) {
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
