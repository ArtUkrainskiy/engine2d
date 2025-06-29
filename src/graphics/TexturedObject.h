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


        float vertexes[] = {
                // Triangle 1: Bottom-left quad triangle
                pos.x, pos.y,                           // Bottom-left
                pos.x + size.x, pos.y,                  // Bottom-right
                pos.x, pos.y + size.y,                  // Top-left
                
                // Triangle 2: Top-right quad triangle
                pos.x + size.x, pos.y,                  // Bottom-right
                pos.x + size.x, pos.y + size.y,        // Top-right
                pos.x, pos.y + size.y                   // Top-left
        };

        float texcoords[] = {
                // Triangle 1: Bottom-left quad triangle
                0.0f, 0.0f,     // Bottom-left
                1.0f, 0.0f,     // Bottom-right
                0.0f, 1.0f,     // Top-left
                
                // Triangle 2: Top-right quad triangle
                1.0f, 0.0f,     // Bottom-right
                1.0f, 1.0f,     // Top-right
                0.0f, 1.0f      // Top-left
        };

        vao->createBuffer(VertexArrayObject::VERTEX_BUFFER, vertexes, 12 * sizeof(float));
        vao->createBuffer(VertexArrayObject::TEXTURE_BUFFER, texcoords, 12 * sizeof(float));
    }

    void setTexture(std::shared_ptr<Texture> texture) {
        this->texture = texture;
        float vertexes[] = {
                // Triangle 1: Bottom-left quad triangle
                position.x, position.y,                                    // Bottom-left
                position.x + texture->getSize().x, position.y,            // Bottom-right
                position.x, position.y + texture->getSize().y,            // Top-left
                
                // Triangle 2: Top-right quad triangle
                position.x + texture->getSize().x, position.y,            // Bottom-right
                position.x + texture->getSize().x, position.y + texture->getSize().y,  // Top-right
                position.x, position.y + texture->getSize().y             // Top-left
        };
        vao->updateBufferData(VertexArrayObject::VERTEX_BUFFER, vertexes, 12 * sizeof(float));
    }

    void setMaterial(std::shared_ptr<Shader> shader) {
        this->shader = shader;
    }

    void draw() override {
        recalculateBuffer();
        texture->bind();
        Object::draw();
    }

protected:
    std::shared_ptr<Texture> texture;

};


#endif //INC_2DSDL_TEXTUREDOBJECT_H
