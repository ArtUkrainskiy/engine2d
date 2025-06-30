//
// Created by artem on 21.05.24.
//

#ifndef ENGINE_ENEMYMANAGER_H
#define ENGINE_ENEMYMANAGER_H


#include <memory>
#include <Engine.h>
#include "EnemyObject.h"
#include "EffectManager.h"

class EnemyManager {
public:
    explicit EnemyManager(const std::shared_ptr<RenderLayer> &newRenderLayer,
                          const std::shared_ptr<CollisionDetector> &newCollisionDetector,
                          const std::shared_ptr<EffectManager> &effectManager) :
            renderLayer(newRenderLayer), collisionDetector(newCollisionDetector), effectManager(effectManager) {

    }

    void addObject(const std::shared_ptr<EnemyObject> &object) {
        renderLayer->addObject(object);
        collisionDetector->addObject(object.get());
        objects.push_back(object);
    }

    void update(float deltaTime) {
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
    std::shared_ptr<RenderLayer> renderLayer;
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::shared_ptr<EffectManager> effectManager;
    std::vector<std::shared_ptr<EnemyObject>> objects;

};


#endif //ENGINE_ENEMYMANAGER_H
