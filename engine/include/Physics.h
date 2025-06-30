#pragma once

#include "physics/CollisionDetector.h"
#include "physics/PhysicObject.h"
// #include "physics/DynamicPhysicsObject.h"

namespace Engine::Physics {
    // Forward all physics classes into the namespace
    using ::CollisionDetector;
    using ::PhysicObject;
    // using ::DynamicPhysicsObject;
}