#ifndef INC_2DSDL_COLLISIONDETECTOR_H
#define INC_2DSDL_COLLISIONDETECTOR_H


#include <cstdint>
#include <vector>
#include "../graphics/Object.h"
#include "../graphics/WireObject.h"


enum CollisionLayer : uint32_t {
    NONE_LAYER     = 0,
    PLAYER_LAYER   = 1 << 0,  // 0001
    ASTEROID_LAYER = 1 << 1,  // 0010
    BULLET_LAYER   = 1 << 2,  // 0100
    POWERUP_LAYER  = 1 << 3,  // 1000
    EFFECT_LAYER   = 1 << 4   // 10000
};

class CollisionDetector final {
public:
    virtual ~CollisionDetector() = default;
    // Template method for automatic layer setup
    template<typename T>
    void addObject(Object* object) {
        setupCollisionMask<T>(object);
        objects.push_back(object);
    }

    // Legacy method for compatibility
    void addObject(Object* object);

    void removeObject(Object *object);

    virtual bool tryMove(Object *object);

    void checkCollisions();


private:
    template<typename T>
    void setupCollisionMask(Object* object) {
        // Default implementation - no collision setup
        static_assert(sizeof(T) == 0, "Unsupported type for collision setup");
    }

    static bool checkCollision(const glm::vec2 &rect1Position, const glm::vec2 &rect1Size,
                        const glm::vec2 &rect2Position, const glm::vec2 &rect2Size);

    std::vector<Object *> objects;
};

// Forward declarations for game objects
class Player;
class ProjectileObject;
class AsteroidObject;
class PowerupObject;

// Template specializations for automatic collision setup
template<>
inline void CollisionDetector::setupCollisionMask<Player>(Object* object) {
    object->setCollisionLayer(PLAYER_LAYER);
    object->setCollisionMask(ASTEROID_LAYER | BULLET_LAYER | POWERUP_LAYER);
}

template<>
inline void CollisionDetector::setupCollisionMask<ProjectileObject>(Object* object) {
    object->setCollisionLayer(BULLET_LAYER);
    object->setCollisionMask(ASTEROID_LAYER | PLAYER_LAYER);
}

// For asteroid types - you can add when needed
template<>
inline void CollisionDetector::setupCollisionMask<AsteroidObject>(Object* object) {
    object->setCollisionLayer(ASTEROID_LAYER);
    object->setCollisionMask(BULLET_LAYER | PLAYER_LAYER);
}

template<>
inline void CollisionDetector::setupCollisionMask<PowerupObject>(Object* object) {
    object->setCollisionLayer(POWERUP_LAYER);
    object->setCollisionMask(PLAYER_LAYER);
}


#endif //INC_2DSDL_COLLISIONDETECTOR_H
