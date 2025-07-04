
#ifndef INC_2DSDL_PHYSICOBJECT_H
#define INC_2DSDL_PHYSICOBJECT_H

#include "../graphics/Object.h"


class IPhysicObject{
public:
    virtual ~IPhysicObject() = default;

    virtual void collide(Object *object){

    }

protected:

};


#endif //INC_2DSDL_PHYSICOBJECT_H
