//
// Created by artem on 28.05.24.
//

#ifndef ENGINE_EFFECTPROTOTYPE_H
#define ENGINE_EFFECTPROTOTYPE_H


#include <Engine.h>

#include "EffectObject.h"

class EffectPrototype {
public:
    EffectPrototype(const std::shared_ptr<Animation> &animation, const std::shared_ptr<Shader> &shader,
                    EffectObject::Type type) : animation(animation), shader(shader), type(type) {
    }

    std::shared_ptr<EffectObject> clone(glm::vec2 position, glm::vec2 size) {
        auto effect = std::make_shared<EffectObject>(position, size, shader, animation->getTexture());
        effect->setAnimation(animation->clone());
        return effect;
    }


private:
    std::shared_ptr<Animation> animation;
    std::shared_ptr<Shader> shader;
    EffectObject::Type type;
};


#endif //ENGINE_EFFECTPROTOTYPE_H
