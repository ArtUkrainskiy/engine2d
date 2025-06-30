//
// Created by artem on 30.04.24.
//

#ifndef INC_2DSDL_TEXTUREDOBJECT_H
#define INC_2DSDL_TEXTUREDOBJECT_H

#include <string>
#include <memory>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "Object.h"
#include "Animation.h"

class TexturedObject : public Object {
public:
    TexturedObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
                   const std::shared_ptr<Texture> &texture) :
            Object(pos, size, shader), texture(texture) {

        // Setup static texture coordinates once
        setupTextureCoordinates();
        // Vertex coordinates will be calculated on demand via recalculateBuffer()
    }

    void setTexture(std::shared_ptr<Texture> texture) {
        if (this->texture != texture) {
            this->texture = texture;
            // Update size to match texture if needed
            if (texture) {
                setSize(texture->getSize());
            }
            // Buffer will be updated on next draw via dirty flagging
        }
    }

    void setMaterial(std::shared_ptr<Shader> shader) {
        this->shader = shader;
    }

    void draw() override {
        if (texture) {
            texture->bind();
        }
        Object::draw(); // Uses optimized dirty flagging
    }

protected:
    std::shared_ptr<Texture> texture;

private:
    void setupTextureCoordinates() {
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

        vao->updateBufferData(VertexArrayObject::TEXTURE_BUFFER, texcoords, 12 * sizeof(float));
    }

};


#endif //INC_2DSDL_TEXTUREDOBJECT_H
