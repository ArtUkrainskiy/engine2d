#ifndef ENGINE_IGAMESCENE_H
#define ENGINE_IGAMESCENE_H

#include <memory>
#include <vector>
#include "InputHandler.h"
#include "../graphics/RenderLayer.h"
class Renderer;

class IGameScene {
public:
    virtual ~IGameScene() = default;

    virtual void initialize() {
        // Create scene-scoped InputHandler
        sceneInputHandler = std::make_unique<InputHandler>();
    }

    virtual void activate() = 0;

    virtual void update(float timeDelta) = 0;

    virtual void deactivate() = 0;

    virtual void destroy() = 0;

    virtual void render(float timeDelta) = 0;

    void addRenderLayer(const std::shared_ptr<RenderLayer>& layer){
        layers.push_back(layer);
    }

    InputHandler* getInputHandler() {
        return sceneInputHandler.get();
    }

protected:
    std::vector<std::shared_ptr<RenderLayer>> layers;
    std::unique_ptr<InputHandler> sceneInputHandler;

};


#endif //ENGINE_IGAMESCENE_H
