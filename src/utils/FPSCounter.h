//
// Created by artem on 18.06.24.
//

#ifndef ENGINE_FPSCOUNTER_H
#define ENGINE_FPSCOUNTER_H

#include <iostream>
#include <chrono>

class FPSCounter {
public:
    FPSCounter() : frameCount(0), fps(0), lastTime(std::chrono::high_resolution_clock::now()), lastFPSTime(std::chrono::high_resolution_clock::now()) {}

    float update() {
        frameCount++;

        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = now - lastTime;
        std::chrono::duration<float> fpsTime = now - lastFPSTime;
        lastTime = now;

        if (fpsTime.count() >= 1.0f) {
            fps = frameCount / fpsTime.count();
            frameCount = 0;
            lastFPSTime = now;
            std::cout << "FPS: " << round(fps) << std::endl;
        }

        return deltaTime.count();
    }

private:
    int frameCount;
    float fps;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFPSTime;
};

#endif //ENGINE_FPSCOUNTER_H
