#include <filesystem>

#include "core/ResourceManager.h"
#include "utils/Utils.h"

namespace fs = std::filesystem;

void ResourceManager::loadResources(const std::string &directory) {
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &entry: std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            std::string name = entry.path().stem().string();
            std::cout << "Loading: " << path << std::endl;
            if (entry.path().extension() == ".vert") {
                std::string vertexPath = entry.path().string();
                std::string fragmentPath = directory;
                fragmentPath.append("/").append(name).append(".frag");

                if (fs::exists(fragmentPath)) {
                    resources[name] = loadShader(vertexPath, fragmentPath);
                }
            } else if (entry.path().extension() == ".png") {
                resources[name] = loadTexture(path);
            } else if (entry.path().extension() == ".wav" || entry.path().extension() == ".mp3") {
                resources[name] = loadSound(path);
            } else if (entry.path().extension() == ".ttf") {
                resources[name] = loadFont(path);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Resources loaded in " << duration.count() << " seconds." << std::endl;

}

std::shared_ptr<Shader> ResourceManager::loadShader(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexCode = Utils::readFile(vertexPath);
    std::string fragmentCode = Utils::readFile(fragmentPath);

    return std::make_shared<Shader>(vertexCode, fragmentCode);
}

std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string &path) {
    return std::make_shared<Texture>(path);
}

std::shared_ptr<Sound> ResourceManager::loadSound(const std::string &path) {
    return std::make_shared<Sound>(path);
}

std::shared_ptr<Font> ResourceManager::loadFont(const std::string &path) {
    return std::make_shared<Font>(path, 16);
}
