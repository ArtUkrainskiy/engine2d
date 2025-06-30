//
// Created by artem on 28.05.24.
//

#ifndef ENGINE_EFFECTMANAGER_H
#define ENGINE_EFFECTMANAGER_H

#include <memory>

#include <Engine.h>

#include "../game/EffectObject.h"
#include "GameEvent.h"
#include "EffectFactory.h"

class EffectManager : public IEventObserver {
public:
    explicit EffectManager(const std::shared_ptr<RenderLayer> &renderLayer) : renderLayer(renderLayer) {
        auto resourceManager = ServiceProvider::get<ResourceManager>();
        ServiceProvider::get<IWindow>()->getInputHandler()->addObserver(this);
        effectFactory = std::make_shared<EffectFactory>();
        auto vfxAnimation = std::make_shared<Animation>(50, resourceManager->get<Texture>("smoke_vfx"));
        vfxAnimation->addFrame({0, 0, 100, 100});
        vfxAnimation->addFrame({100, 0, 200, 100});
        vfxAnimation->addFrame({200, 0, 300, 100});
        vfxAnimation->addFrame({300, 0, 400, 100});
        vfxAnimation->addFrame({400, 0, 500, 100});

        auto explodePrototype = std::make_unique<EffectPrototype>(
                vfxAnimation,
                resourceManager->get<Shader>("rectTextured"),
                EffectObject::DESTROY_ASTEROID
        );
        effectFactory->addPrototype(EffectObject::DESTROY_ASTEROID, std::move(explodePrototype));
    }

    void onGameEvent(GameEvent::EventType event, const std::shared_ptr<Object> &object) {
        switch (event) {
            case GameEvent::DESTROY_ASTEROID:
                auto effect = effectFactory->build(EffectObject::DESTROY_ASTEROID, object->getPosition(),
                                                   object->getSize());
                renderLayer->addObject(effect);
                objects.push_back(effect);
                break;
        }
    }

    void onNotify(SDL_Event &event) override {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            glm::vec2 mousePos(x, y);
            auto effect = effectFactory->build(EffectObject::DESTROY_ASTEROID, glm::vec2(x, y), glm::vec2(100, 100));
            renderLayer->addObject(effect);
            objects.push_back(effect);
        }
    }

    void update(float deltaTime) {
        for (auto it = objects.begin(); it != objects.end();) {
            if (!(*it)->isAlive()) {
                renderLayer->removeObject(*it);
                it = objects.erase(it);
            } else {
                (*it)->update(deltaTime);
                ++it;
            }
        }
    }

private:
    std::shared_ptr<EffectFactory> effectFactory;

    std::shared_ptr<RenderLayer> renderLayer;
    std::vector<std::shared_ptr<EffectObject>> objects;
};


#endif //ENGINE_EFFECTMANAGER_H
