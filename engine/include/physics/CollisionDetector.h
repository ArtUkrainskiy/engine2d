//
// Created by artem on 06.05.24.
//

#ifndef INC_2DSDL_COLLISIONDETECTOR_H
#define INC_2DSDL_COLLISIONDETECTOR_H


#include <vector>
#include <iostream>
#include <algorithm>
#include "../graphics/Object.h"
#include "../graphics/WireObject.h"
#include "PhysicObject.h"

class CollisionDetector {
public:

    void addObject(Object* object) {
        objects.push_back(object);
    }

    void removeObject(Object *object) {
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

    virtual bool tryMove(Object *object) {
        for (const auto &item: objects) {
            if (item == object) {
                continue;
            }
            if (checkCollision(object->getPosition(), object->getSize(),
                               item->getPosition(), item->getSize())) {

                return true;
            }
        }

        return false;
    }

    void checkCollisions() {
        size_t count = objects.size();
        for (size_t i = 0; i < count; ++i) {
            for (size_t j = i + 1; j < count; ++j) {
                if (checkCollision(objects[i]->getPosition(), objects[i]->getSize(),
                                   objects[j]->getPosition(), objects[j]->getSize())) {

                    if(auto physicObject = dynamic_cast<PhysicObject *>(objects[i])){
                        physicObject->collide(objects[j]);
                    }
                    if(auto physicObject = dynamic_cast<PhysicObject *>(objects[j])){
                        physicObject->collide(objects[i]);
                    }

//                    if (auto wireObject = std::dynamic_pointer_cast<WireObject>(objects[i])) {
//                        wireObject->setColor({1, 0, 0, 1});
//                    }
//                    if (auto wireObject = std::dynamic_pointer_cast<WireObject>(objects[j])) {
//                        wireObject->setColor({1, 0, 0, 1});
//                    }

                }
            }
        }
    }


private:
    bool inline checkCollision(const glm::vec2 &rect1Position, const glm::vec2 &rect1Size,
                        const glm::vec2 &rect2Position, const glm::vec2 &rect2Size) {
        if (rect1Position.x + rect1Size.x < rect2Position.x || rect2Position.x + rect2Size.x < rect1Position.x) return false;
        if (rect1Position.y + rect1Size.y < rect2Position.y || rect2Position.y + rect2Size.y < rect1Position.y) return false;
        return true;
    }

    std::vector<Object *> objects;
};


#endif //INC_2DSDL_COLLISIONDETECTOR_H
