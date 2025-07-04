#include "graphics/TexturedObject.h"
#include <iostream>

TexturedObject::TexturedObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
               const std::shared_ptr<Texture> &texture) :
        Object(pos, size, shader), texture(texture) {

    // Setup static texture coordinates once
    setupTextureCoordinates();
    // Vertex coordinates will be calculated on demand via recalculateBuffer()
}

void TexturedObject::setTexture(std::shared_ptr<Texture> texture) {
    if (this->texture != texture) {
        this->texture = texture;
        // Update size to match texture if needed
        if (texture) {
            setSize(texture->getSize());
        }
        // Buffer will be updated on next draw via dirty flagging
    }
}

void TexturedObject::setMaterial(std::shared_ptr<Shader> shader) {
    this->shader = shader;
}

void TexturedObject::draw() {
    if (texture) {
        texture->bind();
    }
    Object::draw(); // Uses optimized dirty flagging
}

void TexturedObject::setupTextureCoordinates() {
    // Setup texture coordinates once - they don't change with position
    static const float texcoords[] = {
            // Triangle 1: Bottom-left quad triangle
            0.0f, 0.0f,     // Bottom-left
            1.0f, 0.0f,     // Bottom-right
            0.0f, 1.0f,     // Top-left
            
            // Triangle 2: Top-right quad triangle
            1.0f, 0.0f,     // Bottom-right
            1.0f, 1.0f,     // Top-right
            0.0f, 1.0f      // Top-left
    };

    if (!vao) {
        std::cerr << "Error: VAO is null in TexturedObject::setupTextureCoordinates()" << std::endl;
        return;
    }

    vao->updateBufferData(VertexArrayObject::TEXTURE_BUFFER, texcoords, 12 * sizeof(float));
}