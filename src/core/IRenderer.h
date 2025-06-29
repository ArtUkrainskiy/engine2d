//
// Created by artem on 14.06.24.
//

#ifndef ENGINE_IRENDERER_H
#define ENGINE_IRENDERER_H


#include <memory>
#include "IGameScene.h"

class IRenderer {
public:
    virtual void init() = 0;
    virtual void setActiveScene(const std::shared_ptr<IGameScene> &scene) = 0;
    virtual void draw() = 0;

protected:
    std::shared_ptr<IGameScene> activeScene;
};


#endif //ENGINE_IRENDERER_H
