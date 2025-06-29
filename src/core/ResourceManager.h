//
// Created by artem on 14.06.24.
//

#ifndef ENGINE_RESOURCEMANAGER_H
#define ENGINE_RESOURCEMANAGER_H


#include "IResourceLoader.h"
#include "../graphics/Font.h"

class ResourceManager : public IResourceLoader {
public:
    void loadResources(const std::string &directory) override;

    template<typename ResourceType>
    std::shared_ptr<ResourceType> get(const std::string &name) {
        auto it = resources.find(name);
        if (it != resources.end()) {
            return std::static_pointer_cast<ResourceType>(it->second);
        }
        return nullptr;
    }

protected:
    std::shared_ptr<Shader> loadShader(const std::string &vertexPath, const std::string &fragmentPath) override;

    std::shared_ptr<Texture> loadTexture(const std::string &path) override;

    std::shared_ptr<Sound> loadSound(const std::string &path) override;

    std::shared_ptr<Font> loadFont(const std::string &path) override;
};


#endif //ENGINE_RESOURCEMANAGER_H
