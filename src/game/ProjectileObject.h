//
// Created by artem on 09.05.24.
//

#ifndef INC_2DSDL_PROJECTILEOBJECT_H
#define INC_2DSDL_PROJECTILEOBJECT_H


#include <glm/vec2.hpp>
#include <iostream>
#include "../graphics/WireObject.h"
#include "../physics/PhysicObject.h"
#include "AsteroidObject.h"
#include "../core/ScoreManager.h"

class ProjectileObject : public WireObject, public PhysicObject {
public:
    enum Owner {
        PLAYER = 0,
        ENEMY
    };

    ProjectileObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color) :
            WireObject(pos, size, shader, color), alive(true), owner(PLAYER) {
    }

    void setAlive(bool newAlive) {
        alive = newAlive;
    }

    bool isAlive() {
        return alive;
    }

    void update(float deltaTime) {
        float angle = getAngle();
        float radians = glm::radians(angle); // Преобразуем градусы в радианы

        // Вычисляем смещение по осям X и Y
        float offsetX = 300 * deltaTime * glm::sin(radians);
        float offsetY = -300 * deltaTime * glm::cos(radians); // Отрицательное значение, так как движение вниз

        // Изменяем позицию объекта с учётом угла
        translate(glm::vec2(offsetX, offsetY));
    }

    void collide(Object *object) override {
        if (auto asteroid = dynamic_cast<AsteroidObject *>(object)) {
            if (owner == PLAYER) {
                if(!asteroid->applyDamage(1)){
                    ServiceProvider::get<ScoreManager>()->addPoints(asteroid->getScore());
                }
                setAlive(false);

            }
        }
    }

    void setOwner(Owner newOwner) {
        owner = newOwner;
    }

    Owner getOwner() {
        return owner;
    }

private:
    bool alive;
    float speed{};
    glm::vec2 direction{};
    Owner owner;

};


#endif //INC_2DSDL_PROJECTILEOBJECT_H
