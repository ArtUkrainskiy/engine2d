cmake_minimum_required(VERSION 3.27)
project(GameEngineProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_CXX_STANDARD 17)

# Добавить движок (всегда)
add_subdirectory(engine)

# Добавить примеры (всегда)
add_subdirectory(examples)

add_subdirectory(asteroids)

# Добавить тесты (если директория существует)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()