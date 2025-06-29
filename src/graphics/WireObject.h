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
        // Buffer will be calculated on first draw via dirty flagging
    }

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }

    void draw() override {
        // Only recalculate buffer if transform changed (inherited from Object)
        if (transform.isDirty() || bufferDirty) {
            recalculateBuffer();
            bufferDirty = false;
        }

        shader->setActive();
        vao->bind();
        shader->setUniform("col", color);
        
        // Get camera matrices - use separate matrices for modern rendering
        if (const auto camera = ServiceProvider::get<Camera>()) {
            shader->setUniform("projection", camera->getProjectionMatrix());
            shader->setUniform("view", camera->getViewMatrix());
            shader->setUniform("model", transform.getModelMatrix());
        } else {
            // Fallback: use identity matrices and model transform as projection
            shader->setUniform("projection", transform.getModelMatrix());
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
        const glm::vec2& pos = getPosition();
        const glm::vec2& objSize = getSize();
        
        float vertexes[] = {
                pos.x, pos.y,                      // Bottom-left
                pos.x + objSize.x, pos.y,          // Bottom-right
                pos.x + objSize.x, pos.y + objSize.y, // Top-right
                pos.x, pos.y + objSize.y           // Top-left
        };
        vao->updateBufferData(VertexArrayObject::VERTEX_BUFFER, vertexes, 8 * sizeof(float));
    }

private:
    glm::vec4 color;
};


#endif //INC_2DSDL_WIREOBJECT_H
