//
// Created by artem on 19.05.24.
//

#ifndef ENGINE_POWERUPOBJECT_H
#define ENGINE_POWERUPOBJECT_H


#include <Engine.h>

class PowerupObject : public TexturedObject, public PhysicObject {
public:
    PowerupObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
                  const std::shared_ptr<Texture> &texture, int type) : TexturedObject(pos, size, shader, texture), type(type) {

    }

    bool isAlive(){
        return alive;
    }

    void setAlive(bool newAlive){
        alive = newAlive;
    }

    void update(float timeDelta){
        translate({0, 100 * timeDelta});
    }

    int getType(){
        return type;
    }

private:
    int type;
    bool alive = true;
};


#endif //ENGINE_POWERUPOBJECT_H
