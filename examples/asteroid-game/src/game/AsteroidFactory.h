//
// Created by artem on 09.05.24.
//

#ifndef INC_2DSDL_ASTEROIDFACTORY_H
#define INC_2DSDL_ASTEROIDFACTORY_H


#include <iostream>

#include <glm/gtx/string_cast.hpp>

#include "AsteroidObject.h"
#include "AsteroidPrototype.h"

class AsteroidFactory {
public:
    void setSpawnArea(glm::vec4 newSpawnArea) {
        spawnArea = newSpawnArea;
    }

    void setTargetArea(glm::vec4 newTargetArea) {
        targetArea = newTargetArea;
    }

    void addPrototype(AsteroidPrototype::Size size, const std::shared_ptr<AsteroidPrototype> &prototype) {
        prototypes.push_back(prototype);
    }

    std::shared_ptr<AsteroidObject> build(AsteroidPrototype::Size size) {
        glm::vec2 position = Utils::getRandomVec2(
                {glm::vec2(spawnArea.x, spawnArea.y), glm::vec2(spawnArea.z, spawnArea.w)});
        glm::vec2 target = Utils::getRandomVec2(
                {glm::vec2(targetArea.x, targetArea.y), glm::vec2(targetArea.z, targetArea.w)});
        return prototypes[size]->createAsteroid(position, target);

    }

    std::shared_ptr<AsteroidObject> buildRandom() {
        std::default_random_engine engine(time(nullptr));
        std::uniform_int_distribution<int> sizeDist(0, prototypes.size() - 1);
        int index = sizeDist(engine);
        glm::vec2 position = Utils::getRandomVec2(
                {glm::vec2(spawnArea.x, spawnArea.y), glm::vec2(spawnArea.z, spawnArea.w)});
        glm::vec2 target = Utils::getRandomVec2(
                {glm::vec2(targetArea.x, targetArea.y), glm::vec2(targetArea.z, targetArea.w)});
        return prototypes[index]->createAsteroid(position, target);
    }

private:
    glm::vec4 spawnArea;
    glm::vec4 targetArea;
    std::vector<std::shared_ptr<AsteroidPrototype>> prototypes;
};

#endif //INC_2DSDL_ASTEROIDFACTORY_H
