cmake_minimum_required(VERSION 3.22)
project(GameEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

# Найти пакеты SDL2 и OpenGL
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(GLEW REQUIRED)

# Apple Silicon support
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        find_package(glm REQUIRED)
        include_directories(/opt/homebrew/include)
        link_directories(/opt/homebrew/lib)
        add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
    endif()
endif()

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2TTF_INCLUDE_DIR})

# Создать библиотеку движка
add_library(GameEngine STATIC
    # Core
        core/ServiceProvider.cpp
        core/EventDispatcher.cpp
        core/InputHandler.cpp
        core/ResourceManager.cpp
        core/SceneManager.cpp
        core/Camera.cpp
        core/Transform.cpp
    
    # Graphics
        graphics/SDL2Window.cpp
        graphics/Texture.cpp
        graphics/Shader.cpp
        graphics/VertexArrayObject.cpp
        graphics/Animation.cpp
        graphics/AnimationController.cpp
        graphics/BatchObject.cpp
        graphics/InstancedBatchObject.cpp
        graphics/Object.cpp
        graphics/TexturedObject.cpp
        graphics/RenderLayer.cpp
        graphics/WireObject.cpp
        graphics/Renderer.cpp
        graphics/Scene.cpp

        # Physics
        physics/CollisionDetector.cpp
        # src/physics/DynamicPhysicsObject.cpp  # Требует Box2D
    
    # Sounds
        sounds/Sound.cpp
        sounds/SoundPlayer.cpp
    
    # UI
        ui/Button.cpp
        ui/TextLabel.cpp
        ui/UIBuilder.cpp
    
    # Utils
        utils/Utils.cpp
        utils/CallbackTimer.cpp
    
    # Math
)

# Публичные заголовки
target_include_directories(GameEngine 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    INTERFACE
        $<INSTALL_INTERFACE:include>
)

# Линковка зависимостей
target_link_libraries(GameEngine 
    PUBLIC
        SDL2::SDL2
        SDL2::SDL2main
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARY}
        ${SDL2TTF_LIBRARY}
        GLEW::GLEW
        ${OPENGL_LIBRARIES}
)

# Установка компилятора флагов для профилирования (если нужно)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")