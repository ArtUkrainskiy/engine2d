//
// Created by artem on 28.05.24.
//

#ifndef ENGINE_EFFECTOBJECT_H
#define ENGINE_EFFECTOBJECT_H


#include "../graphics/TexturedObject.h"

class EffectObject : public TexturedObject {
public:
    using TexturedObject::TexturedObject;

    enum Type{
        DESTROY_ASTEROID = 0,
        DESTROY_ENEMY,
        _COUNT,
    };

    void setAnimation(std::shared_ptr<Animation> newAnimation){
        animation = std::move(newAnimation);
    }


    bool isAlive(){
        return alive;
    }

    void update(float deltaTime){
        if (animation) {
            alive = !animation->play();
            auto coords = animation->getCurrentFrame();
            auto size = texture->getSize();

            float texcoords[] = {
                    // Triangle 1: Bottom-left quad triangle
                    coords.x / size.x, coords.y / size.y,      // Bottom-left
                    (coords.z) / size.x, coords.y / size.y,    // Bottom-right
                    coords.x / size.x, (coords.w) / size.y,    // Top-left
                    
                    // Triangle 2: Top-right quad triangle
                    (coords.z) / size.x, coords.y / size.y,    // Bottom-right
                    (coords.z) / size.x, (coords.w) / size.y,  // Top-right
                    coords.x / size.x, (coords.w) / size.y     // Top-left
            };

            vao->updateBufferData(VertexArrayObject::TEXTURE_BUFFER, texcoords, 12 * sizeof(float));
        }

    }

private:
    bool alive = true;

    std::shared_ptr<Animation> animation;

};


#endif //ENGINE_EFFECTOBJECT_H
