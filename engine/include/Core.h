#pragma once

#include "core/GameEngine.h"
#include "core/ServiceProvider.h"
#include "core/ServiceInitializer.h"
#include "core/SceneManager.h"
#include "core/Camera.h"
#include "core/Transform.h"
#include "core/EventDispatcher.h"
#include "core/InputHandler.h"
#include "core/ResourceManager.h"
#include "core/IEventObserver.h"
#include "core/IGameScene.h"
#include "core/IRenderer.h"
#include "core/IResourceLoader.h"
#include "core/IWindow.h"

namespace Engine::Core {
    // Forward all core classes into the namespace
    using ::GameEngine;
    using ::ServiceProvider;
    using ::SceneManager;
    using ::Camera;
    using ::Transform;
    using ::EventDispatcher;
    using ::InputHandler;
    using ::ResourceManager;
    using ::IEventObserver;
    using ::IGameScene;
    using ::IRenderer;
    using ::IResourceLoader;
    using ::IWindow;
}