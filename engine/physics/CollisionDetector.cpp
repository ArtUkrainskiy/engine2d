#include "physics/CollisionDetector.h"
#include <algorithm>
#include <iostream>

#include "PhysicObject.h"

void CollisionDetector::addObject(Object* object) {
    if (!object) {
        std::cerr << "Warning: Attempting to add null object to collision detector" << std::endl;
        return;
    }
    objects.push_back(object);
}

void CollisionDetector::removeObject(Object *object) {
    if (!object) {
        std::cerr << "Warning: Attempting to remove null object from collision detector" << std::endl;
        return;
    }
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

bool CollisionDetector::tryMove(Object *object) {
    if (!object) {
        std::cerr << "Warning: tryMove called with null object" << std::endl;
        return false;
    }
    
    for (const auto &item: objects) {
        if (item == object) {
            continue;
        }
        if (!item) {
            std::cerr << "Warning: Found null object in collision detector" << std::endl;
            continue;
        }
        
        if (checkCollision(object->getPosition(), object->getSize(),
                           item->getPosition(), item->getSize())) {
            return true;
        }
    }
    
    return false;
}

void CollisionDetector::checkCollisions() {
    size_t count = objects.size();
    for (size_t i = 0; i < count; ++i) {
        if (!objects[i]) {
            std::cerr << "Warning: Found null object at index " << i << " in collision detector" << std::endl;
            continue;
        }
        
        for (size_t j = i + 1; j < count; ++j) {
            if (!objects[j]) {
                std::cerr << "Warning: Found null object at index " << j << " in collision detector" << std::endl;
                continue;
            }
            
            // Check if objects can collide using bitmasks
            if (!objects[i]->canCollideWith(objects[j])) {
                continue;
            }
            
            if (checkCollision(objects[i]->getPosition(), objects[i]->getSize(),
                               objects[j]->getPosition(), objects[j]->getSize())) {
                
                if(auto physicObject = dynamic_cast<IPhysicObject *>(objects[i])) {
                    try {
                        physicObject->collide(objects[j]);
                    } catch (const std::exception& e) {
                        std::cerr << "Error in collision callback for object " << i << ": " << e.what() << std::endl;
                    }
                }
                if(auto physicObject = dynamic_cast<IPhysicObject *>(objects[j])) {
                    try {
                        physicObject->collide(objects[i]);
                    } catch (const std::exception& e) {
                        std::cerr << "Error in collision callback for object " << j << ": " << e.what() << std::endl;
                    }
                }
            }
        }
    }
}

bool CollisionDetector::checkCollision(const glm::vec2 &rect1Position, const glm::vec2 &rect1Size,
                                     const glm::vec2 &rect2Position, const glm::vec2 &rect2Size) {
    // Check for invalid rectangles
    if (rect1Size.x <= 0 || rect1Size.y <= 0 || rect2Size.x <= 0 || rect2Size.y <= 0) {
        return false;
    }
    
    // AABB collision detection
    if (rect1Position.x + rect1Size.x < rect2Position.x || rect2Position.x + rect2Size.x < rect1Position.x) {
        return false;
    }
    if (rect1Position.y + rect1Size.y < rect2Position.y || rect2Position.y + rect2Size.y < rect1Position.y) {
        return false;
    }
    
    return true;
}

