//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_TEXTURE_H
#define INC_2DSDL_TEXTURE_H

#include <iostream>
#include <string_view>

#include <SDL2/SDL_image.h>
#include <GLES3/gl3.h>
#include <glm/vec2.hpp>

#include "Resource.h"

class Texture : public Resource {
public:
    explicit Texture(std::string_view path);

    explicit Texture(SDL_Surface *surface);

    [[nodiscard]] GLuint getTexture() const;

    void bind();

    glm::vec2 getSize();

    ~Texture();

private:
    GLuint texture{};
    glm::vec2 size;
};


#endif //INC_2DSDL_TEXTURE_H
