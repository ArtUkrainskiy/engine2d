#ifndef INC_2DSDL_UTILS_H
#define INC_2DSDL_UTILS_H


#include <string>
#include <random>
#include <glm/glm.hpp>

class Utils {
public:
    static std::string readFile(const std::string &filename);

    static uint32_t getRandomValue(const std::pair<uint32_t, uint32_t>& range);

    static float getRandomFloat(const std::pair<float, float>& range);

    static glm::vec2 getRandomVec2(const std::pair<glm::vec2, glm::vec2>& range);
};


#endif //INC_2DSDL_UTILS_H
