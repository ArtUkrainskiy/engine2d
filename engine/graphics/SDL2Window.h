#ifndef INC_2DSDL_WINDOW_H
#define INC_2DSDL_WINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include "../core/IEventObserver.h"
#include "../core/InputHandler.h"
#include "../core/IWindow.h"


class SDL2Window final : public IWindow, public IEventObserver {
public:
    SDL2Window(uint16_t width, uint16_t height, const std::string& title);


    int init() override;


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
    InputHandler *inputHandler{};
    std::string title;
    bool fullFPS{};
};


#endif //INC_2DSDL_WINDOW_H
