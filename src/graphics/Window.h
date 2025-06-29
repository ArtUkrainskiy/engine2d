//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_WINDOW_H
#define INC_2DSDL_WINDOW_H


#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include "../core/IEventObserver.h"
#include "../core/InputHandler.h"
#include "../core/IWindow.h"


class Window : public IWindow, public IEventObserver {
public:
    Window(uint16_t width, uint16_t height);


    int init() final;


    bool update() override;

    void onNotify(SDL_Event &event) override {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    InputHandler *getInputHandler() override{
        return inputHandler;
    }

    glm::vec2 getWindowSize() final{
        return {width, height};
    }

private:
    SDL_Window *window{};
    InputHandler *inputHandler;
};


#endif //INC_2DSDL_WINDOW_H
