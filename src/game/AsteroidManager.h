//
// Created by artem on 10.05.24.
//

#ifndef INC_2DSDL_ASTEROIDMANAGER_H
#define INC_2DSDL_ASTEROIDMANAGER_H


#include "AsteroidObject.h"
#include "../graphics/RenderLayer.h"
#include "../physics/CollisionDetector.h"

class AsteroidManager {
public:
    explicit AsteroidManager(const std::shared_ptr<RenderLayer> &newRenderLayer,
                             const std::shared_ptr<CollisionDetector> &newCollisionDetector) :
            renderLayer(newRenderLayer), collisionDetector(newCollisionDetector) {

    }

    void addObject(const std::shared_ptr<AsteroidObject> &object) {
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
    std::vector<std::shared_ptr<AsteroidObject>> objects;

};


#endif //INC_2DSDL_ASTEROIDMANAGER_H
