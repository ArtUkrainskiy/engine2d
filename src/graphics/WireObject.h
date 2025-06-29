//
// Created by artem on 06.05.24.
//

#ifndef INC_2DSDL_WIREOBJECT_H
#define INC_2DSDL_WIREOBJECT_H

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "VertexArrayObject.h"
#include "Object.h"
#include "../core/ServiceProvider.h"
#include "../core/Camera.h"

class WireObject : public Object {
public:
    WireObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color) :
            Object(pos, size, shader), color(color) {

        recalculateBuffer();
    }

    void setColor(glm::vec4 newColor){
        color = newColor;
    }

    void draw() override {
        recalculateBuffer();

        shader->setActive();
        vao->bind();
        shader->setUniform("col", color);
        
        // Get camera matrices - use separate matrices for modern rendering
        if (const auto camera = ServiceProvider::get<Camera>()) {
            shader->setUniform("projection", camera->getProjectionMatrix());
            shader->setUniform("view", camera->getViewMatrix());
            shader->setUniform("model", getModelMatrix());
        } else {
            // Fallback: use identity matrices and model transform as projection
            shader->setUniform("projection", getModelMatrix());
            shader->setUniform("view", glm::mat4(1.0f));
            shader->setUniform("model", glm::mat4(1.0f));
        }
        
        glDrawArraysInstanced(GL_LINE_LOOP, 0, 4, 1);
        for (const auto &item: childs){
            item->draw();
        }
    }

    void recalculateBuffer() override {
        // WireObject needs 4 vertices for GL_LINE_LOOP (rectangle outline)
        float vertexes[] = {
                position.x, position.y,                    // Bottom-left
                position.x + size.x, position.y,          // Bottom-right
                position.x + size.x, position.y + size.y, // Top-right
                position.x, position.y + size.y           // Top-left
        };
        vao->updateBufferData(VertexArrayObject::VERTEX_BUFFER, vertexes, 8 * sizeof(float));
    }

private:
    glm::vec4 color;
};


#endif //INC_2DSDL_WIREOBJECT_H
