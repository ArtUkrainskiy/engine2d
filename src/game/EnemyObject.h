//
// Created by artem on 20.05.24.
//

#ifndef ENGINE_ENEMYOBJECT_H
#define ENGINE_ENEMYOBJECT_H


#include "../graphics/TexturedObject.h"
#include "../physics/PhysicObject.h"
#include "../utils/CallbackTimer.h"
#include "ProjectilePool.h"
#include <glm/gtx/string_cast.hpp>

class EnemyObject : public TexturedObject, public PhysicObject {
public:
    EnemyObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
                const std::shared_ptr<Texture> &texture, const std::shared_ptr<ProjectilePool> &projectilePool) :
            TexturedObject(pos, size, shader, texture), projectilePool(projectilePool) {
        x = pos.x;

        weaponTimer = std::make_unique<CallbackTimer>();
        weaponTimer->addCallback(
                [this, projectilePool]() {
                    projectilePool->getProjectile(getCenterPosition(), 180, ProjectileObject::ENEMY);
                },
                333);
    }

    void setCenterPosition(glm::vec2 center) {
        Object::setCenterPosition(center);
        x = getPosition().x;
    }


    void update(float deltaTime) {
        setAngle(0);
        float xOffset = 150 * cos(SDL_GetTicks() / 1000.0f * 1);
        setPosition({x + xOffset, position.y += 50 * deltaTime});
        weaponTimer->update();
    }

    bool isAlive(){
        return alive;
    }

    void applyDamage(uint32_t damage){
        health -= damage;
        if(health <= 0){
            alive = false;
        }
    }

    void collide(Object *object) override{
        if(auto projectile = dynamic_cast<ProjectileObject *>(object)){
            if (projectile->getOwner() == ProjectileObject::PLAYER) {
                this->applyDamage(1);
                projectile->setAlive(false);
            }
        }
    }

private:
    int health = 3;
    bool alive = true;
    float x = 0;
    std::unique_ptr<CallbackTimer> weaponTimer;
    std::shared_ptr<ProjectilePool> projectilePool;
};


#endif //ENGINE_ENEMYOBJECT_H
