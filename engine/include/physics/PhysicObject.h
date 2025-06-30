//
// Created by artem on 06.05.24.
//

#ifndef INC_2DSDL_PHYSICOBJECT_H
#define INC_2DSDL_PHYSICOBJECT_H

#include <memory>
#include "../graphics/Object.h"


class PhysicObject{
public:

    virtual void collide(Object *object){

    }

protected:

};


#endif //INC_2DSDL_PHYSICOBJECT_H
