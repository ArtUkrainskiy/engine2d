//
// Created by artem on 10.05.24.
//

#ifndef INC_2DSDL_ASTEROIDMANAGER_H
#define INC_2DSDL_ASTEROIDMANAGER_H


#include "AsteroidObject.h"
#include "EffectManager.h"
#include "GameEvent.h"
#include "AsteroidFactory.h"

class AsteroidManager {
public:
    explicit AsteroidManager(const std::shared_ptr<RenderLayer> &newRenderLayer,
                             const std::shared_ptr<CollisionDetector> &newCollisionDetector,
                             const std::shared_ptr<EffectManager> &effectManager) :
            renderLayer(newRenderLayer), collisionDetector(newCollisionDetector), effectManager(effectManager) {
        auto resourceManager = ServiceProvider::get<ResourceManager>();

        asteroidFactory = std::make_unique<AsteroidFactory>();
        asteroidFactory->setSpawnArea(glm::vec4(0, -150, 800, -150));
        asteroidFactory->setTargetArea(glm::vec4(-50, 650, 850, 650));
        asteroidFactory->addPrototype(
                AsteroidPrototype::SMALL,
                std::make_shared<AsteroidPrototype>(
                        resourceManager->get<Texture>("asteroid2"),
                        resourceManager->get<Shader>("rectTextured"),
                        std::make_pair(35, 50),
                        std::make_pair(50.f, 350.f),
                        1,
                        10
                )
        );
        asteroidFactory->addPrototype(
                AsteroidPrototype::MEDIUM,
                std::make_shared<AsteroidPrototype>(
                        resourceManager->get<Texture>("asteroid3"),
                        resourceManager->get<Shader>("rectTextured"),
                        std::make_pair(45, 55),
                        std::make_pair(30.f, 250.f),
                        2,
                        20
                )
        );
        asteroidFactory->addPrototype(
                AsteroidPrototype::LARGE,
                std::make_shared<AsteroidPrototype>(
                        resourceManager->get<Texture>("asteroid4"),
                        resourceManager->get<Shader>("rectTextured"),
                        std::make_pair(55, 65),
                        std::make_pair(25.f, 150.f),
                        3,
                        30
                )
        );
        callbackTimer = std::make_unique<CallbackTimer>();
        // Таймер спавнит астероиды раз в n мс
        callbackTimer->addCallback(
            [this]() { addObject(asteroidFactory->build(AsteroidPrototype::SMALL)); },
            300 * 2);

        callbackTimer->addCallback(
            [this]() { addObject(asteroidFactory->build(AsteroidPrototype::MEDIUM)); },
            500 * 2);

        callbackTimer->addCallback(
            [this]() { addObject(asteroidFactory->build(AsteroidPrototype::LARGE)); },
            750 * 2);

    }

    void addObject(const std::shared_ptr<AsteroidObject> &object) {
        renderLayer->addObject(object);
        collisionDetector->addObject<AsteroidObject>(object.get());
        objects.push_back(object);
    }

    void update(float deltaTime) {
        callbackTimer->update();
        for (auto it = objects.begin(); it != objects.end();) {
            if (!(*it)->isAlive() or (*it)->getCenterPosition().y >= 700) {
                effectManager->onGameEvent(GameEvent::DESTROY_ASTEROID, *it);
                renderLayer->removeObject(*it);
                collisionDetector->removeObject(it->get());
                it = objects.erase(it);
            } else {
                (*it)->update(deltaTime);
                ++it;
            }
        }
    }

private:
    std::shared_ptr<AsteroidFactory> asteroidFactory;
    std::shared_ptr<RenderLayer> renderLayer;
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::shared_ptr<EffectManager> effectManager;
    std::unique_ptr<CallbackTimer> callbackTimer;

    std::vector<std::shared_ptr<AsteroidObject>> objects;

};


#endif //INC_2DSDL_ASTEROIDMANAGER_H
