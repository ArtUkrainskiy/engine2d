//
// Created by artem on 07.04.24.
//

#include <SDL2/SDL_image.h>
#include <iostream>
#include "graphics/Texture.h"

Texture::Texture(std::string_view path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    SDL_Surface *textureSurface = IMG_Load(path.data());
    if (!textureSurface) {
        std::cerr << "Error loading texture" << std::endl;
//        throw new Exception();
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSurface->w, textureSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 textureSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    size = {textureSurface->w, textureSurface->h};
    SDL_FreeSurface(textureSurface);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

GLuint Texture::getTexture() const {
    return texture;
}

Texture::Texture(SDL_Surface *surface) {

    auto rgbSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgbSurface->w, rgbSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 rgbSurface->pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    size = {rgbSurface->w, rgbSurface->h};
    SDL_FreeSurface(rgbSurface);
}

glm::vec2 Texture::getSize() {
    return size;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}
