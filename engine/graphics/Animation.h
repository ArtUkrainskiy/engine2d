#pragma once

#include <glm/vec4.hpp>
#include <vector>
#include <chrono>
#include <memory>
#include "Texture.h"

class Animation {
public:
    Animation(int frameDelayMs, std::shared_ptr<Texture> texture);

    std::shared_ptr<Animation> clone();

    void addFrame(glm::vec4 coords);

    bool play();

    glm::vec4 getCurrentFrame();

    void reset();

    std::shared_ptr<Texture> getTexture();

private:
    std::shared_ptr<Texture> texture;
    std::vector<glm::vec4> frames;
    int curFrame = 0;
    int frameDelayMs = 100;
    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();
};