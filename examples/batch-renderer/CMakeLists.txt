cmake_minimum_required(VERSION 3.27)
project(BatchRendererDemo)

add_executable(BatchRendererDemo
    src/main.cpp
    src/BatchedObject.cpp
    src/BatchInstance.cpp
)

target_link_libraries(BatchRendererDemo PRIVATE GameEngine)

# Копировать ресурсы
add_custom_command(TARGET BatchRendererDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:BatchRendererDemo>/assets
)