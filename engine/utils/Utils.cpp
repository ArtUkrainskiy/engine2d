#include "utils/Utils.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

std::string Utils::readFile(const std::string &filename) {
    if (filename.empty()) {
        std::cerr << "Error: Empty filename provided to readFile" << std::endl;
        throw std::invalid_argument("Empty filename");
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        throw std::runtime_error("Failed to open file " + filename);
    }

    try {
        // Get the size of the file
        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (size == 0) {
            std::cerr << "Warning: File " << filename << " is empty" << std::endl;
            return "";
        }

        // Read the entire file into a string
        std::string content(size, ' ');
        file.read(content.data(), size);

        if (file.fail() && !file.eof()) {
            std::cerr << "Error: Failed to read from file " << filename << std::endl;
            throw std::runtime_error("Failed to read from file " + filename);
        }

        return content;
    } catch (const std::exception& e) {
        std::cerr << "Error reading file " << filename << ": " << e.what() << std::endl;
        throw;
    }
}

uint32_t Utils::getRandomValue(const std::pair<uint32_t, uint32_t>& range) {
    if (range.first > range.second) {
        std::cerr << "Error: Invalid range for getRandomValue: " << range.first << " > " << range.second << std::endl;
        return range.first;
    }

    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> dist(range.first, range.second);
        return dist(gen);
    } catch (const std::exception& e) {
        std::cerr << "Error generating random value: " << e.what() << std::endl;
        return range.first;
    }
}

float Utils::getRandomFloat(const std::pair<float, float>& range) {
    if (range.first > range.second) {
        std::cerr << "Error: Invalid range for getRandomFloat: " << range.first << " > " << range.second << std::endl;
        return range.first;
    }

    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(range.first, range.second);
        return dist(gen);
    } catch (const std::exception& e) {
        std::cerr << "Error generating random float: " << e.what() << std::endl;
        return range.first;
    }
}

glm::vec2 Utils::getRandomVec2(const std::pair<glm::vec2, glm::vec2>& range) {
    if (range.first.x > range.second.x || range.first.y > range.second.y) {
        std::cerr << "Error: Invalid range for getRandomVec2" << std::endl;
        return range.first;
    }

    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> xDist(range.first.x, range.second.x);
        std::uniform_real_distribution<float> yDist(range.first.y, range.second.y);
        return glm::vec2(xDist(gen), yDist(gen));
    } catch (const std::exception& e) {
        std::cerr << "Error generating random vec2: " << e.what() << std::endl;
        return range.first;
    }
}