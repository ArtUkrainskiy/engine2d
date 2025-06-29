//
// Created by artem on 20.05.24.
//

#ifndef ENGINE_POWERUPMANAGER_H
#define ENGINE_POWERUPMANAGER_H


#include "PowerupObject.h"
#include "../physics/CollisionDetector.h"
#include "../graphics/RenderLayer.h"
#include "../utils/CallbackTimer.h"
#include "../core/ServiceProvider.h"
#include "../core/ResourceManager.h"
#include "PowerupFactory.h"

class PowerupManager {
public:
    explicit PowerupManager(const std::shared_ptr<RenderLayer> &newRenderLayer,
                             const std::shared_ptr<CollisionDetector> &newCollisionDetector) :
            renderLayer(newRenderLayer), collisionDetector(newCollisionDetector) {
        auto resourceManager = ServiceProvider::get<ResourceManager>();

        powerupFactory = std::make_shared<PowerupFactory>();
        powerupFactory->setSpawnArea(glm::vec4(0, -150, 800, -150));
        powerupFactory->addPrototype(PowerupPrototype::REPAIR_BONUS, std::move(
                                             std::make_unique<PowerupPrototype>(
                                                     resourceManager->get<Texture>("repair_bonus"),
                                                     resourceManager->get<Shader>("rectTextured"),
                                                     PowerupPrototype::REPAIR_BONUS)
                                     )
        );
        powerupFactory->addPrototype(PowerupPrototype::WEAPON_UPGRADE, std::move(
                                             std::make_unique<PowerupPrototype>(
                                                     resourceManager->get<Texture>("weapon_upgrade"),
                                                     resourceManager->get<Shader>("rectTextured"),
                                                     PowerupPrototype::WEAPON_UPGRADE)
                                     )
        );
        callbackTimer = std::make_unique<CallbackTimer>();

        callbackTimer->addCallback(
                [this]() {
                    addObject(powerupFactory->build(PowerupPrototype::REPAIR_BONUS));
                },
                7000);

        callbackTimer->addCallback(
                [this]() {
                    addObject(powerupFactory->build(PowerupPrototype::WEAPON_UPGRADE));
                },
                9000);

    }

    void addObject(const std::shared_ptr<PowerupObject> &object) {
        renderLayer->addObject(object);
        collisionDetector->addObject(object.get());
        objects.push_back(object);
    }

    void update(float deltaTime) {
        callbackTimer->update();
        for (auto it = objects.begin(); it != objects.end();) {
            if (!(*it)->isAlive() or (*it)->getCenterPosition().y >= 700) {
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
    std::shared_ptr<PowerupFactory> powerupFactory;
    std::unique_ptr<CallbackTimer> callbackTimer;
    std::shared_ptr<RenderLayer> renderLayer;
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::vector<std::shared_ptr<PowerupObject>> objects;

};

#endif //ENGINE_POWERUPMANAGER_H
