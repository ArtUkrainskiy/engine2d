//
// Created by artem on 19.05.24.
//

#ifndef ENGINE_POWERUPFACTORY_H
#define ENGINE_POWERUPFACTORY_H


#include <glm/vec4.hpp>
#include <memory>
#include <vector>

#include "PowerupPrototype.h"
#include "PowerupObject.h"


class PowerupFactory {
public:
    void setSpawnArea(glm::vec4 newSpawnArea) {
        spawnArea = newSpawnArea;
    }

    void addPrototype(int type, std::unique_ptr<PowerupPrototype> prototype){
        prototypes[type] = std::move(prototype);
    }

    std::shared_ptr<PowerupObject> build(int type){
        glm::vec2 position = Utils::getRandomVec2({glm::vec2(spawnArea.x, spawnArea.y), glm::vec2(spawnArea.z, spawnArea.w)});
        return prototypes[type]->clone(position);
    }

private:
    std::unique_ptr<PowerupPrototype> prototypes[PowerupPrototype::_COUNT];
    glm::vec4 spawnArea;
};


#endif //ENGINE_POWERUPFACTORY_H
