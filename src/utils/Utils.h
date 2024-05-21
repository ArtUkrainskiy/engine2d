//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_UTILS_H
#define INC_2DSDL_UTILS_H


#include <string>
#include <fstream>
#include <random>
#include <glm/glm.hpp>

class Utils {
public:
    static std::string readFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file " + filename);
        }

        // Get the size of the file
        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        // Read the entire file into a string
        std::string content(size, ' ');
        file.read(content.data(), size);

        return content;
    }

    static uint32_t getRandomValue(const std::pair<uint32_t, uint32_t>& range) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> dist(range.first, range.second);
        return dist(gen);
    }

    static float getRandomFloat(const std::pair<float, float>& range) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(range.first, range.second);
        return dist(gen);
    }

    static glm::vec2 getRandomVec2(const std::pair<glm::vec2, glm::vec2>& range) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> xDist(range.first.x, range.second.x);
        std::uniform_real_distribution<float> yDist(range.first.y, range.second.y);
        return glm::vec2(xDist(gen), yDist(gen));
    }
};


#endif //INC_2DSDL_UTILS_H
