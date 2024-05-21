//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_WINDOW_H
#define INC_2DSDL_WINDOW_H


#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include "../core/EventObserver.h"


class Window : public EventObserver{


public:
    Window(uint16_t width, uint16_t height);

    int init();


    bool update();

    void onNotify(SDL_Event &event) override {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

private:
    bool running;

    uint16_t width;
    uint32_t height;

    SDL_Window *window{};
};


#endif //INC_2DSDL_WINDOW_H
