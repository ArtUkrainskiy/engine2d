//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_RENDERER_H
#define INC_2DSDL_RENDERER_H

#include "Scene.h"


class Renderer {

public:
    void setScene(const std::shared_ptr<Scene> &scene) {
        activeScene = scene;
    }

    void draw() {
        //TODO: refactoring
        glClearColor(0., 0., 0., 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        activeScene->draw();
    }

private:
    std::shared_ptr<Scene> activeScene;
};


#endif //INC_2DSDL_RENDERER_H
