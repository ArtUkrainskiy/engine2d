cmake_minimum_required(VERSION 3.27)
project(engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_CXX_STANDARD 17)
# Найти пакеты SDL2 и OpenGL
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

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
        src/physics/DynamicPhysicsObject.cpp
        src/graphics/TextRenderer.cpp
        src/graphics/TexturedObject.cpp
        src/graphics/RenderLayer.cpp
        src/graphics/OpenGLRenderer.cpp
        src/utils/Utils.cpp
        src/core/InputHandler.cpp
        src/core/EventObserver.cpp
        src/game/Player.cpp
        src/graphics/WireObject.cpp
        src/physics/CollisionDetector.cpp
        src/physics/PhysicObject.cpp
        src/math/ObjectTransform.cpp
        src/game/AsteroidObject.cpp
        src/game/PlayerShip.cpp
        src/game/ProjectileObject.cpp
        src/game/AsteroidManager.cpp
        src/game/AsteroidBuilder.cpp
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
        src/graphics/ShaderManager.cpp
        src/graphics/ShaderManager.h
        src/game/EnemyObject.cpp
        src/game/EnemyObject.h
)

# Связать библиотеки
target_link_libraries(engine PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARY}
        ${SDL2TTF_LIBRARY}
        GLEW::GLEW
        ${OPENGL_LIBRARIES}
)

add_executable(game src/game/main.cpp)

target_link_libraries(game engine)