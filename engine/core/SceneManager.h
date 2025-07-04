#ifndef ENGINE_SCENEMANAGER_H
#define ENGINE_SCENEMANAGER_H

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <type_traits>
#include "IGameScene.h"

class SceneManager {
public:
    SceneManager() = default;

    // Create scene by type
    template<typename SceneImpl>
    std::shared_ptr<SceneImpl> createScene() {
        static_assert(std::is_base_of_v<IGameScene, SceneImpl>, "Scene must inherit from IGameScene");
        
        auto scene = std::make_shared<SceneImpl>();
        scene->initialize();
        scenes[typeid(SceneImpl)] = scene;
        return scene;
    }

    // Create scene with custom name
    template<typename SceneImpl>
    std::shared_ptr<SceneImpl> createScene(const std::string& name) {
        static_assert(std::is_base_of_v<IGameScene, SceneImpl>, "Scene must inherit from IGameScene");
        
        auto scene = std::make_shared<SceneImpl>();
        scene->initialize();
        scenes[typeid(SceneImpl)] = scene;
        namedScenes[name] = scene;
        return scene;
    }

    // Activate by type
    template<typename SceneImpl>
    bool activateScene() {
        auto it = scenes.find(typeid(SceneImpl));
        if (it != scenes.end()) {
            switchToScene(it->second);
            return true;
        }
        return false;
    }

    // Activate by name
    bool activateScene(const std::string& name);

    // Legacy method for compatibility
    template<typename SceneImpl>
    bool activate() {
        return activateScene<SceneImpl>();
    }

    // Get scene by type
    template<typename SceneImpl>
    std::shared_ptr<SceneImpl> getScene() {
        auto it = scenes.find(typeid(SceneImpl));
        if (it != scenes.end()) {
            return std::static_pointer_cast<SceneImpl>(it->second);
        }
        return nullptr;
    }

    // Get scene by name
    std::shared_ptr<IGameScene> getScene(const std::string& name);

    std::shared_ptr<IGameScene> getActiveScene() const;

    // Check if scene exists
    template<typename SceneImpl>
    bool hasScene() const {
        return scenes.find(typeid(SceneImpl)) != scenes.end();
    }

    bool hasScene(const std::string& name) const;

    // Remove scene
    template<typename SceneImpl>
    void removeScene() {
        auto it = scenes.find(typeid(SceneImpl));
        if (it != scenes.end()) {
            if (activeScene == it->second) {
                activeScene->deactivate();
                activeScene = nullptr;
            }
            it->second->destroy();
            scenes.erase(it);
        }
    }

    void removeScene(const std::string& name);

    void clear();

private:
    void switchToScene(std::shared_ptr<IGameScene> newScene);

    std::unordered_map<std::type_index, std::shared_ptr<IGameScene>> scenes;
    std::unordered_map<std::string, std::shared_ptr<IGameScene>> namedScenes;
    std::shared_ptr<IGameScene> activeScene = nullptr;
};

#endif //ENGINE_SCENEMANAGER_H
