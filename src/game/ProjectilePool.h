//
// Created by artem on 16.05.24.
//

#ifndef INC_2DSDL_PROJECTILEPOOL_H
#define INC_2DSDL_PROJECTILEPOOL_H


#include <vector>
#include "ProjectileObject.h"
#include "../graphics/RenderLayer.h"
#include "../physics/CollisionDetector.h"

class ProjectilePool {
public:
    ProjectilePool(const std::shared_ptr<Shader> &shader, const std::shared_ptr<RenderLayer> &layer,
                   const std::shared_ptr<CollisionDetector> &newCollisionDetector) :
            projectileShader(shader), renderLayer(layer), collisionDetector(newCollisionDetector) {}

    void getProjectile(glm::vec2 position, float angle, ProjectileObject::Owner owner) {
        auto projectile = std::make_shared<ProjectileObject>(
                position,
                glm::vec2(2, 3),
                projectileShader,
                glm::vec4(1, 1, 1, 1)
        );
        projectile->setAngle(angle);
        projectile->setCenterPosition(position);
        projectile->setOwner(owner);
        activeProjectiles.push_back(projectile);
        collisionDetector->addObject(projectile.get());
        renderLayer->addObject(projectile);
    }

    void update(float deltaTime) {
        for (auto it = activeProjectiles.begin(); it != activeProjectiles.end();) {
            if ((*it)->getPosition().y <= 0 or (*it)->getPosition().y >= 600 or not (*it)->isAlive()) {
                renderLayer->removeObject(*it);
                collisionDetector->removeObject(it->get());
                it = activeProjectiles.erase(it);
            } else {
                (*it)->update(deltaTime);
                ++it;
            }
        }
    }

private:
    std::shared_ptr<Shader> projectileShader;
    std::shared_ptr<RenderLayer> renderLayer;
    std::shared_ptr<CollisionDetector> collisionDetector;

    std::vector<std::shared_ptr<ProjectileObject>> activeProjectiles;
};


#endif //INC_2DSDL_PROJECTILEPOOL_H
