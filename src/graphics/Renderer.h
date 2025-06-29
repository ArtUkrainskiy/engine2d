//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_RENDERER_H
#define INC_2DSDL_RENDERER_H

#include "Scene.h"
#include "../core/IRenderer.h"
#include "../core/ServiceProvider.h"
#include "../core/Camera.h"
#include "../core/IWindow.h"


class Renderer: public IRenderer {
public:
    void init() final {
        // Initialize any renderer-specific resources
        
        // Set up window resize callback for camera updates
        if (const auto window = ServiceProvider::get<IWindow>()) {
            // Note: This would require adding resize callback support to IWindow
            // For now, camera resize handling will be done manually
        }
    }

    void setActiveScene(const std::shared_ptr<IGameScene> &scene) final{
        activeScene = scene;
    }

    void draw() final {
        // Update camera if window size changed
        updateCameraIfNeeded();
        
        glClearColor(0., 0., 0., 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void updateCameraIfNeeded() {
        if (const auto window = ServiceProvider::get<IWindow>()) {
            if (const auto camera = ServiceProvider::get<Camera>()) {
                const auto currentWindowSize = window->getWindowSize();
                if (camera->getWindowSize() != currentWindowSize) {
                    camera->setWindowSize(currentWindowSize);
                }
            }
        }
    }
};


#endif //INC_2DSDL_RENDERER_H
