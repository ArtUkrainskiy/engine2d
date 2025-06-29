//
// Created by artem on 18.05.24.
//

#ifndef INC_2DSDL_BUTTON_H
#define INC_2DSDL_BUTTON_H


#include <functional>
#include "../graphics/WireObject.h"
#include "../core/IEventObserver.h"
#include "../core/ServiceProvider.h"
#include "../core/Camera.h"

class Button : public WireObject, public IEventObserver {
public:
    Button(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color) :
            WireObject(pos, size, shader, color) {
    }


    void onNotify(SDL_Event &event) override {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            glm::vec2 mousePos(x, y);
            
            // Convert screen coordinates to world coordinates using camera
            if (const auto camera = ServiceProvider::get<Camera>()) {
                mousePos = camera->screenToWorld(mousePos);
            }

            if (isInside(mousePos, this->position, this->size)) {
                clicked();
            }
        }
    }

    void onClick(const std::function<void()>& callback) {
        clickCallback = callback;
    }


    void clicked(){
        if(clickCallback){
            clickCallback();
        }
    }

private:
    std::function<void()> clickCallback;

    bool isInside(const glm::vec2 &point, const glm::vec2 &pos, const glm::vec2 &size) {
        return (point.x >= pos.x && point.x <= pos.x + size.x && point.y >= pos.y && point.y <= pos.y + size.y);
    }
};


#endif //INC_2DSDL_BUTTON_H
