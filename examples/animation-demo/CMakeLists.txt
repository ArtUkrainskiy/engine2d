cmake_minimum_required(VERSION 3.27)
project(AnimationDemo)

add_executable(AnimationDemo
    src/main.cpp
)

target_link_libraries(AnimationDemo PRIVATE GameEngine)

# Копировать ресурсы
add_custom_command(TARGET AnimationDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:AnimationDemo>/assets
)