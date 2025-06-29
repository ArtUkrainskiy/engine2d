cmake_minimum_required(VERSION 3.27)
project(engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_CXX_STANDARD 17)
# Найти пакеты SDL2 и OpenGL
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2TTF REQUIRED)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        find_package(glm REQUIRED)
        include_directories(/opt/homebrew/include)
        link_directories(/opt/homebrew/lib)
        add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
    endif()
endif ()

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2TTF_INCLUDE_DIR})

# Добавить исполняемый файл
ADD_LIBRARY(engine
        src/graphics/Window.cpp
        src/graphics/Texture.cpp
        src/graphics/Shader.cpp
        src/graphics/VertexArrayObject.cpp
        src/graphics/Animation.cpp
        src/graphics/AnimationController.cpp
        src/graphics/Object.cpp
        src/sounds/SoundPlayer.cpp
#        src/physics/DynamicPhysicsObject.cpp
        src/graphics/TextRenderer.cpp
        src/graphics/TexturedObject.cpp
        src/graphics/RenderLayer.cpp
        src/graphics/OpenGLRenderer.cpp
        src/utils/Utils.cpp
        src/core/InputHandler.cpp
        src/core/IEventObserver.cpp
        src/game/Player.cpp
        src/graphics/WireObject.cpp
        src/physics/CollisionDetector.cpp
        src/physics/PhysicObject.cpp
        src/math/ObjectTransform.cpp
        src/game/AsteroidObject.cpp
        src/game/PlayerShip.cpp
        src/game/ProjectileObject.cpp
        src/game/AsteroidManager.cpp
        src/game/AsteroidFactory.cpp
        src/game/AsteroidPrototype.cpp
        src/utils/CallbackTimer.cpp
        src/game/ProjectilePool.cpp
        src/UI/Button.cpp
        src/game/PowerupObject.cpp
        src/game/PowerupObject.h
        src/game/PowerupFactory.cpp
        src/game/PowerupFactory.h
        src/game/PowerupPrototype.cpp
        src/game/PowerupPrototype.h
        src/game/PowerupManager.cpp
        src/game/PowerupManager.h
        src/game/EnemyObject.cpp
        src/game/EnemyObject.h
        src/game/EnemyManager.cpp
        src/game/EnemyManager.h
        src/game/EffectManager.cpp
        src/game/EffectManager.h
        src/game/EffectFactory.cpp
        src/game/EffectFactory.h
        src/game/GameEvent.cpp
        src/game/GameEvent.h
        src/game/EffectPrototype.cpp
        src/game/EffectPrototype.h
        src/game/EffectObject.cpp
        src/game/EffectObject.h
        src/game/GameMaster.cpp
        src/game/GameMaster.h
        src/core/EventDispatcher.cpp
        src/core/EventDispatcher.h
        src/core/IGameScene.h
        src/graphics/Resource.h
        src/UI/UIBuilder.cpp
        src/UI/UIBuilder.h
        src/core/ServiceProvider.cpp
        src/core/ServiceProvider.h
        src/core/ServiceInitializer.h
        src/core/Engine.cpp
        src/core/Engine.h
        src/core/IWindow.h
        src/core/IRenderer.h
        src/core/IResourceLoader.h
        src/core/ResourceManager.cpp
        src/core/ResourceManager.h
        src/utils/FPSCounter.h
        src/core/SceneManager.cpp
        src/core/SceneManager.h
        src/UI/TextLabel.cpp
        src/UI/TextLabel.h
        src/core/ScoreManager.cpp
        src/core/ScoreManager.h
        src/core/Upgrade.cpp
        src/core/Upgrade.h
        src/core/UpgradeTree.cpp
        src/core/UpgradeTree.h
        src/core/UpgradeManager.cpp
        src/core/UpgradeManager.h
        src/core/Camera.cpp
        src/core/Camera.h
)

# Связать библиотеки
target_link_libraries(engine PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARY}
        ${SDL2TTF_LIBRARY}
        ${OPENGL_LIBRARIES}
)

add_executable(game src/game/main.cpp
        src/game/MenuScene.cpp
        src/game/MenuScene.h)

target_link_libraries(game engine)

##############################################################
###########################EXAMPLES###########################
##############################################################

add_executable(AnimatedObject src/examples/AnimatedObject.cpp)
target_link_libraries(AnimatedObject engine)
add_executable(EventsExample src/examples/EventsExample.cpp
        src/examples/SceneExample.cpp
        src/examples/MenuScene.h
        src/examples/GameScene.h
        src/examples/ScoreScene.h
        src/examples/HUDInterface.cpp
        src/examples/HUDInterface.h)
target_link_libraries(EventsExample engine)

add_executable(batch_renderer
        src/batch_renderer/main.cpp
        src/batch_renderer/BatchedObject.cpp
        src/batch_renderer/BatchInstance.cpp
)
target_link_libraries(batch_renderer engine)

