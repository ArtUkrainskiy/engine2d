cmake_minimum_required(VERSION 3.27)
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
    src/core/Engine.cpp
    src/core/ServiceProvider.cpp
    src/core/EventDispatcher.cpp
    src/core/IEventObserver.cpp
    src/core/InputHandler.cpp
    src/core/ResourceManager.cpp
    src/core/SceneManager.cpp
    src/core/Camera.cpp
    
    # Graphics
    src/graphics/Window.cpp
    src/graphics/Texture.cpp
    src/graphics/Shader.cpp
    src/graphics/VertexArrayObject.cpp
    src/graphics/Animation.cpp
    src/graphics/AnimationController.cpp
    src/graphics/Object.cpp
    src/graphics/TextRenderer.cpp
    src/graphics/TexturedObject.cpp
    src/graphics/RenderLayer.cpp
    src/graphics/OpenGLRenderer.cpp
    src/graphics/WireObject.cpp
    src/graphics/Renderer.cpp
    src/graphics/Scene.cpp
    src/graphics/Tile.cpp
    
    # Physics
    src/physics/CollisionDetector.cpp
    src/physics/PhysicObject.cpp
    # src/physics/DynamicPhysicsObject.cpp  # Требует Box2D
    
    # Sounds
    src/sounds/SoundPlayer.cpp
    
    # UI
    src/ui/Button.cpp
    src/ui/TextLabel.cpp
    src/ui/UIBuilder.cpp
    
    # Utils
    src/utils/Utils.cpp
    src/utils/CallbackTimer.cpp
    
    # Math
    src/math/Vector.cpp
    src/math/Rectangle.cpp
)

# Публичные заголовки
target_include_directories(GameEngine 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
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