//
// Created by artem on 12.06.24.
//

#ifndef ENGINE_SERVICEINITIALIZER_H
#define ENGINE_SERVICEINITIALIZER_H


#include <type_traits>

#include "ServiceProvider.h"

#include "EventDispatcher.h"
#include "IRenderer.h"
#include "IWindow.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"

class ServiceInitializer {
public:
    template<typename WindowImpl>
    typename std::enable_if<std::is_base_of<IWindow, WindowImpl>::value, IWindow*>::type
    createWindow(int width, int height) {
        window = new WindowImpl(width, height);
        window->init();
        ServiceProvider::provide<IWindow>(window);
        return window;
    }

    template<typename RendererImpl>
    typename std::enable_if<std::is_base_of<IRenderer, RendererImpl>::value, IRenderer*>::type
    createRenderer() {
        renderer = new RendererImpl();
        renderer->init();
        ServiceProvider::provide<IRenderer>(renderer);
        return renderer;
    }

    ResourceManager *createResourceManager() {
        resourceManager = new ResourceManager();
        ServiceProvider::provide<ResourceManager>(resourceManager);
        return resourceManager;
    }

    EventDispatcher *createEventDispatcher() {
        eventDispatcher = new EventDispatcher();
        ServiceProvider::provide<EventDispatcher>(eventDispatcher);
        return eventDispatcher;
    }

    SceneManager *createSceneManager() {
        sceneManager = new SceneManager();
        ServiceProvider::provide<SceneManager>(sceneManager);
        return sceneManager;
    }

    Camera *createCamera(glm::vec2 windowSize) {
        camera = new Camera(windowSize);
        ServiceProvider::provide<Camera>(camera);
        return camera;
    }

    template<typename ServiceImpl>
    ServiceImpl *createService(){
        auto service = new ServiceImpl();
        ServiceProvider::provide<ServiceImpl>(service);
        return service;
    }

protected:
    IWindow *window = nullptr;
    IRenderer *renderer = nullptr;
    ResourceManager *resourceManager = nullptr;
    EventDispatcher *eventDispatcher = nullptr;
    SceneManager *sceneManager = nullptr;
    Camera *camera = nullptr;
};


#endif //ENGINE_SERVICEINITIALIZER_H
