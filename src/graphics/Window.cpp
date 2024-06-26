//
// Created by artem on 07.04.24.
//

#include "Window.h"

#include <GLES3/gl3.h>


Window::Window(uint16_t width, uint16_t height) : width(width), height(height) {
    running = true;
}


int Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Установка профиля OpenGL Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    SDL_GL_SetAttribute(static_cast<SDL_GLattr>(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG), 1);
#endif

    window = SDL_CreateWindow("Blue Paper Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

//    SDL_GL_SetSwapInterval(0);
//
//    glewExperimental = GL_TRUE;
//    glewInit();

    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "GL Version: " << version << std::endl;
    std::cout << "GL Shaders: " << shaderVersion << std::endl;
    return 0;
}

bool Window::update() {
    SDL_GL_SwapWindow(window);
    return running;
}



