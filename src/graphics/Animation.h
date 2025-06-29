#pragma once

#include <glm/vec4.hpp>
#include <vector>
#include <chrono>
#include <memory>
#include "Texture.h"

class Animation {
public:
    Animation(int frameDelayMs, std::shared_ptr<Texture> texture) : frameDelayMs(frameDelayMs),
                                                                    texture(std::move(texture)) {

    }

    std::shared_ptr<Animation> clone(){
        auto clone = std::make_shared<Animation>(frameDelayMs, texture);
        clone->frames = frames;
        return clone;
    }

    void addFrame(glm::vec4 coords) {
        frames.push_back(coords);
    }

    bool play() {
        auto now = std::chrono::steady_clock::now();
        if (now - lastFrameTime >= std::chrono::milliseconds(frameDelayMs)) {
            curFrame++;
            if (curFrame >= frames.size()) {
                curFrame = 0;
            }
            lastFrameTime = now;
        }
        return curFrame == frames.size() - 1;
    }

    glm::vec4 getCurrentFrame() {
        return frames[curFrame];
    }

    void reset() {
        curFrame = 0;
    }

    std::shared_ptr<Texture> getTexture() {
        return texture;
    }

private:
    std::shared_ptr<Texture> texture;
    std::vector<glm::vec4> frames;
    int curFrame = 0;
    int frameDelayMs = 100;
    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();
};