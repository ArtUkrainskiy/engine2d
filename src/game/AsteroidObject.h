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

    bool applyDamage(int damage){
        health -= damage;
        if(health > 0){
            return true;
        }else{
            alive = false;
            return false;
        }
    }

    void initialize(int newHealth, int newScore){
        health = newHealth;
        score = newScore;
    }

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
        setAngle(getAngle() + rotationSpeed * deltaTime);
        translatePosition(direction * speed * deltaTime);
    }

    bool isAlive() const {
        return alive;
    }

    void setAlive(bool newAlive) {
        alive = newAlive;
    }

    int getScore() const{
        return score;
    }

    int getHealth() const{
        return health;
    }

private:
    float speed;
    bool alive = true;
    int health;
    int score;
    glm::vec2 target;
    glm::vec2 direction;

    float rotationSpeed;
};


#endif //INC_2DSDL_ASTEROIDOBJECT_H
