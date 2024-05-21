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

class TexturedObject : public Object {
public:
    TexturedObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
                   const std::shared_ptr<Texture> &texture) :
            Object(pos, size, shader), texture(texture) {


        float vertexes[] = {
                pos.x, pos.y,
                pos.x + size.x, pos.y,
                pos.x + size.x, pos.y + size.y,
                pos.x, pos.y + size.y
        };

        float texcoords[] = {
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f
        };

        vao->createBuffer(VertexArrayObject::VERTEX_BUFFER, vertexes, 8 * sizeof(float));
        vao->createBuffer(VertexArrayObject::TEXTURE_BUFFER, texcoords, 8 * sizeof(float));
    }

    void setTexture(std::shared_ptr<Texture> texture) {
        this->texture = texture;
        float vertexes[] = {
                position.x, position.y,
                position.x + texture->getSize().x, position.y,
                position.x + texture->getSize().x, position.y + texture->getSize().y,
                position.x, position.y + texture->getSize().y
        };
        vao->updateBufferData(VertexArrayObject::VERTEX_BUFFER, vertexes, 8 * sizeof(float));

    }


    void setMaterial(std::shared_ptr<Shader> shader) {
        this->shader = shader;
    }

    virtual void draw() {
        texture->bind();
        Object::draw();
    }

private:
    std::shared_ptr<Texture> texture;

};


#endif //INC_2DSDL_TEXTUREDOBJECT_H
