#include "ui/Button.h"
#include <iostream>
#include <core/Camera.h>
#include <core/ServiceProvider.h>

Button::Button(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color) :
        WireObject(pos, size, shader, color) {
    if (!shader) {
        std::cerr << "Warning: Button created with null shader" << std::endl;
    }
}

void Button::onNotify(SDL_Event &event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        glm::vec2 mousePos(x, y);
        
        // Convert screen coordinates to world coordinates using camera
        if (const auto camera = ServiceProvider::get<Camera>()) {
            mousePos = camera->screenToWorld(mousePos);
        } else {
            std::cerr << "Warning: No camera available for button coordinate conversion" << std::endl;
        }

        if (isInside(mousePos, this->getPosition(), this->getSize())) {
            clicked();
        }
    }
}

void Button::onClick(const std::function<void()>& callback) {
    clickCallback = callback;
}

void Button::clicked() {
    if (clickCallback) {
        try {
            clickCallback();
        } catch (const std::exception& e) {
            std::cerr << "Error in button click callback: " << e.what() << std::endl;
        }
    }
}

bool Button::isInside(const glm::vec2 &point, const glm::vec2 &pos, const glm::vec2 &size) {
    return (point.x >= pos.x && point.x <= pos.x + size.x && 
            point.y >= pos.y && point.y <= pos.y + size.y);
}