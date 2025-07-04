#ifndef ENGINE_IRESOURCELOADER_H
#define ENGINE_IRESOURCELOADER_H


#include <memory>
#include <string>
#include <unordered_map>

#include "../graphics/Font.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../sounds/SoundPlayer.h"

class IResourceLoader {
public:
    virtual ~IResourceLoader() = default;
    virtual void loadResources(const std::string &directory) = 0;

protected:
    virtual std::shared_ptr<Shader> loadShader(const std::string &vertexPath, const std::string &fragmentPath) = 0;

    virtual std::shared_ptr<Texture> loadTexture(const std::string &path) = 0;

    virtual std::shared_ptr<Sound> loadSound(const std::string &path) = 0;

    virtual std::shared_ptr<Font> loadFont(const std::string &path) = 0;

    std::unordered_map<std::string, std::shared_ptr<IResource>> resources;
};


#endif //ENGINE_IRESOURCELOADER_H
