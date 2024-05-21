//
// Created by artem on 20.05.24.
//

#ifndef ENGINE_SHADERMANAGER_H
#define ENGINE_SHADERMANAGER_H


#include <memory>
#include <string>
#include <unordered_map>
#include "Shader.h"

class ShaderManager {
public:
    static ShaderManager &getInstance() {
        static ShaderManager instance;
        return instance;
    }

    void loadShaders(const std::string &directory);

    std::shared_ptr<Shader> getShader(const std::string &name);

    ShaderManager(const ShaderManager &) = delete;

    ShaderManager &operator=(const ShaderManager &) = delete;

private:
    ShaderManager() {}

    ~ShaderManager() = default;


    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

    std::string readShaderCode(const std::string &filePath);

    std::shared_ptr<Shader> createShader(const std::string &vertexPath, const std::string &fragmentPath);
};

#endif //ENGINE_SHADERMANAGER_H
