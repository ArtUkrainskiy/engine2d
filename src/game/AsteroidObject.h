//
// Created by artem on 09.05.24.
//

#ifndef INC_2DSDL_ASTEROIDOBJECT_H
#define INC_2DSDL_ASTEROIDOBJECT_H


#include <iostream>
#include "../graphics/TexturedObject.h"

class AsteroidObject : public TexturedObject {
public:
    using TexturedObject::TexturedObject;

    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    void setRotationSpeed(float newRotationSpeed){
        rotationSpeed = newRotationSpeed;
    }

    void setTarget(glm::vec2 newTarget) {
        target = newTarget;
        direction = glm::normalize(target - position);
    }

    void update(float deltaTime) {
        setAngle(rotationSpeed * deltaTime);
        movePosition(direction * speed * deltaTime);
    }

    bool isAlive() {
        return alive;
    }

    void setAlive(bool newAlive) {
        alive = newAlive;
    }

private:
    float speed;
    bool alive = true;
    glm::vec2 target;
    glm::vec2 direction;

    float rotationSpeed;
};


#endif //INC_2DSDL_ASTEROIDOBJECT_H
