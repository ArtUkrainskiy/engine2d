//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_INPUTHANDLER_H
#define INC_2DSDL_INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "EventObserver.h"

class InputHandler {
public:
    void handleInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            notify(event);
        }
    }

    void addObserver(EventObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(EventObserver* observer) {
        // реализация удаления наблюдателя
    }

private:
    void notify(SDL_Event& event) {
        for (auto observer : observers) {
            observer->onNotify(event);
        }
    }

    std::vector<EventObserver*> observers;
};



#endif //INC_2DSDL_INPUTHANDLER_H
