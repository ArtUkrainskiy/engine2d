//
// Created by artem on 19.05.24.
//

#ifndef ENGINE_POWERUPPROTOTYPE_H
#define ENGINE_POWERUPPROTOTYPE_H


#include <memory>

#include <Engine.h>

#include "PowerupObject.h"

class PowerupPrototype {
public:
    enum type {
        REPAIR_BONUS = 0,
        WEAPON_UPGRADE,
        _COUNT
    };

    PowerupPrototype(const std::shared_ptr<Texture> &texture, const std::shared_ptr<Shader> &shader, type type)
            : texture(texture), shader(shader), type(type) {

    }

    std::shared_ptr<PowerupObject> clone(glm::vec2 position) {
        return std::make_shared<PowerupObject>(position, texture->getSize(), shader, texture, type);
    }


private:
    type type;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
};


#endif //ENGINE_POWERUPPROTOTYPE_H
