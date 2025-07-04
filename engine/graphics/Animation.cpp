#include "graphics/Animation.h"
#include <iostream>

Animation::Animation(const int frameDelayMs, std::shared_ptr<Texture> texture)
    : texture(std::move(texture)), frameDelayMs(frameDelayMs) {
    if (frameDelayMs <= 0) {
        std::cerr << "Warning: Invalid frame delay " << frameDelayMs << "ms, using 100ms instead" << std::endl;
        this->frameDelayMs = 100;
    }
    if (!this->texture) {
        std::cerr << "Warning: Animation created with null texture" << std::endl;
    }
}

std::shared_ptr<Animation> Animation::clone() {
    auto clone = std::make_shared<Animation>(frameDelayMs, texture);
    clone->frames = frames;
    return clone;
}

void Animation::addFrame(const glm::vec4 coords) {
    frames.push_back(coords);
}

bool Animation::play() {
    if (frames.empty()) {
        return false;
    }

    if (const auto now = std::chrono::steady_clock::now(); now - lastFrameTime >=
        std::chrono::milliseconds(frameDelayMs)) {
        curFrame++;
        if (curFrame >= frames.size()) {
            curFrame = 0;
        }
        lastFrameTime = now;
    }
    return curFrame == frames.size() - 1;
}

glm::vec4 Animation::getCurrentFrame() {
    if (frames.empty()) {
        std::cerr << "Warning: getCurrentFrame() called on empty animation" << std::endl;
        return glm::vec4(0.0f);
    }
    if (curFrame >= frames.size()) {
        std::cerr << "Warning: Invalid frame index " << curFrame << ", resetting to 0" << std::endl;
        curFrame = 0;
    }
    return frames[curFrame];
}

void Animation::reset() {
    curFrame = 0;
    lastFrameTime = std::chrono::steady_clock::now();
}

std::shared_ptr<Texture> Animation::getTexture() {
    return texture;
}
