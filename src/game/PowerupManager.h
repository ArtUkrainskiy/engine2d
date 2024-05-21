//
// Created by artem on 20.05.24.
//

#ifndef ENGINE_POWERUPMANAGER_H
#define ENGINE_POWERUPMANAGER_H


#include "PowerupObject.h"
#include "../physics/CollisionDetector.h"
#include "../graphics/RenderLayer.h"

class PowerupManager {
public:
    explicit PowerupManager(const std::shared_ptr<RenderLayer> &newRenderLayer,
                             const std::shared_ptr<CollisionDetector> &newCollisionDetector) :
            renderLayer(newRenderLayer), collisionDetector(newCollisionDetector) {

    }

    void addObject(const std::shared_ptr<PowerupObject> &object) {
        renderLayer->addObject(object);
        collisionDetector->addObject(object.get());
        objects.push_back(object);
    }

    void update(float deltaTime) {
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
    std::shared_ptr<RenderLayer> renderLayer;
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::vector<std::shared_ptr<PowerupObject>> objects;

};

#endif //ENGINE_POWERUPMANAGER_H
