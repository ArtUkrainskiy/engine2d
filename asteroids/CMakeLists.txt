cmake_minimum_required(VERSION 3.22)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

# Находим зависимости
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


# Главный исполняемый файл
add_executable(asteroids
    main.cpp
)

# Подключаем движок
target_link_libraries(asteroids GameEngine)
