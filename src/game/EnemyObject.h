//
// Created by artem on 20.05.24.
//

#ifndef ENGINE_ENEMYOBJECT_H
#define ENGINE_ENEMYOBJECT_H


#include "../graphics/TexturedObject.h"
#include "../physics/PhysicObject.h"

class EnemyObject : public TexturedObject, public PhysicObject {
public:
    using TexturedObject::TexturedObject;

};


#endif //ENGINE_ENEMYOBJECT_H
