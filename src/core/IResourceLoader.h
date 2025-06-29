//
// Created by artem on 14.06.24.
//

#ifndef ENGINE_IRESOURCELOADER_H
#define ENGINE_IRESOURCELOADER_H


#include <string>
#include <unordered_map>
#include <memory>
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../sounds/SoundPlayer.h"
#include "../graphics/Font.h"

class IResourceLoader {
public:
    virtual void loadResources(const std::string &directory) = 0;

protected:
    virtual std::shared_ptr<Shader> loadShader(const std::string &vertexPath, const std::string &fragmentPath) = 0;

    virtual std::shared_ptr<Texture> loadTexture(const std::string &path) = 0;

    virtual std::shared_ptr<Sound> loadSound(const std::string &path) = 0;

    virtual std::shared_ptr<Font> loadFont(const std::string &path) = 0;

    std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
};


#endif //ENGINE_IRESOURCELOADER_H
