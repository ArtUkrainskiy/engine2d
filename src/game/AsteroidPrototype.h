//
// Created by artem on 10.05.24.
//

#ifndef INC_2DSDL_ASTEROIDPROTOTYPE_H
#define INC_2DSDL_ASTEROIDPROTOTYPE_H


#include <memory>
#include <utility>
#include <cstdint>

#include <glm/glm.hpp>

#include "../graphics/Texture.h"
#include "AsteroidObject.h"
#include "../utils/Utils.h"

class AsteroidPrototype {
public:
    enum Size {
        SMALL, MEDIUM, LARGE
    };

    AsteroidPrototype(const std::shared_ptr<Texture> &texture, const std::shared_ptr<Shader> &shader,
                      const std::pair<uint32_t, uint32_t> &sizeRange,
                      const std::pair<float, float> &speedRange,
                      int health, int score
                      )
            : texture(texture), shader(shader), sizeRange(sizeRange), speedRange(speedRange), health(health), score(score) {

    }

    std::shared_ptr<AsteroidObject> createAsteroid(glm::vec2 position, glm::vec2 target) {
        auto size = Utils::getRandomValue(sizeRange);
        auto speed = Utils::getRandomFloat(speedRange);

        auto asteroid = std::make_shared<AsteroidObject>(position, glm::vec2(size, size), shader, texture);
        asteroid->setAngle(Utils::getRandomFloat({0.f, 360.f}));
        asteroid->setRotationSpeed(Utils::getRandomFloat({-150, 150}));
        asteroid->setSpeed(speed);
        asteroid->setTarget(target);
        asteroid->initialize(health, score);
        return asteroid;
    }

private:
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
    std::pair<uint32_t, uint32_t> sizeRange;
    std::pair<float, float> speedRange;
    int health;
    int score;
};


#endif //INC_2DSDL_ASTEROIDPROTOTYPE_H
