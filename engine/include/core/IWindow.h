//
// Created by artem on 12.06.24.
//

#ifndef ENGINE_IWINDOW_H
#define ENGINE_IWINDOW_H

#include <cstdint>
#include <string>
#include <glm/vec2.hpp>

#include "InputHandler.h"

class IWindow{
public:
    virtual bool update() = 0;
    virtual int init() = 0;
    virtual InputHandler* getInputHandler() = 0;
    virtual glm::vec2 getWindowSize() = 0;
protected:
    bool running;

    uint32_t width;
    uint32_t height;

};

#endif //ENGINE_IWINDOW_H
