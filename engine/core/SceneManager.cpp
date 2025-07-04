#include "core/SceneManager.h"
#include <iostream>

// Activate by name
bool SceneManager::activateScene(const std::string& name) {
    if (name.empty()) {
        std::cerr << "Error: Empty scene name provided to activateScene" << std::endl;
        return false;
    }

    auto it = namedScenes.find(name);
    if (it != namedScenes.end()) {
        switchToScene(it->second);
        return true;
    }
    
    std::cerr << "Warning: Scene '" << name << "' not found" << std::endl;
    return false;
}

// Get scene by name
std::shared_ptr<IGameScene> SceneManager::getScene(const std::string& name) {
    if (name.empty()) {
        std::cerr << "Error: Empty scene name provided to getScene" << std::endl;
        return nullptr;
    }

    auto it = namedScenes.find(name);
    return (it != namedScenes.end()) ? it->second : nullptr;
}

std::shared_ptr<IGameScene> SceneManager::getActiveScene() const {
    return activeScene;
}

bool SceneManager::hasScene(const std::string& name) const {
    if (name.empty()) {
        return false;
    }
    return namedScenes.find(name) != namedScenes.end();
}

void SceneManager::removeScene(const std::string& name) {
    if (name.empty()) {
        std::cerr << "Error: Empty scene name provided to removeScene" << std::endl;
        return;
    }

    auto it = namedScenes.find(name);
    if (it != namedScenes.end()) {
        auto scene = it->second;
        
        // Check if it's the active scene
        if (activeScene == scene) {
            try {
                activeScene->deactivate();
            } catch (const std::exception& e) {
                std::cerr << "Error deactivating scene '" << name << "': " << e.what() << std::endl;
            }
            activeScene = nullptr;
        }
        
        // Destroy the scene
        try {
            scene->destroy();
        } catch (const std::exception& e) {
            std::cerr << "Error destroying scene '" << name << "': " << e.what() << std::endl;
        }
        
        namedScenes.erase(it);
        
        // Also remove from type-based map if present
        for (auto typeIt = scenes.begin(); typeIt != scenes.end(); ++typeIt) {
            if (typeIt->second == scene) {
                scenes.erase(typeIt);
                break;
            }
        }
    } else {
        std::cerr << "Warning: Scene '" << name << "' not found for removal" << std::endl;
    }
}

void SceneManager::clear() {
    // Deactivate current scene
    if (activeScene) {
        try {
            activeScene->deactivate();
        } catch (const std::exception& e) {
            std::cerr << "Error deactivating active scene during clear: " << e.what() << std::endl;
        }
        activeScene = nullptr;
    }
    
    // Destroy all scenes
    for (auto& [type, scene] : scenes) {
        try {
            if (scene) {
                scene->destroy();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error destroying scene during clear: " << e.what() << std::endl;
        }
    }
    
    scenes.clear();
    namedScenes.clear();
}

void SceneManager::switchToScene(std::shared_ptr<IGameScene> newScene) {
    if (!newScene) {
        std::cerr << "Error: Attempting to switch to null scene" << std::endl;
        return;
    }

    // Deactivate current scene if different
    if (activeScene && activeScene != newScene) {
        try {
            activeScene->deactivate();
        } catch (const std::exception& e) {
            std::cerr << "Error deactivating current scene: " << e.what() << std::endl;
        }
    }
    
    // Set new active scene
    activeScene = newScene;
    
    // Activate new scene
    if (activeScene) {
        try {
            activeScene->activate();
        } catch (const std::exception& e) {
            std::cerr << "Error activating new scene: " << e.what() << std::endl;
            activeScene = nullptr; // Reset on failure
        }
    }
}