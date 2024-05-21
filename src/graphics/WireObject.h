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

class WireObject : public Object {
public:
    WireObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color) :
            Object(pos, size, shader), color(color) {

        Object::recalculateBuffer();
    }

    void setColor(glm::vec4 newColor){
        color = newColor;
    }

    void draw() override {
        shader->setActive();
        vao->bind();
        shader->setUniform("col", color);
        glDrawArraysInstanced(GL_LINE_LOOP, 0, 4, 1);
    }

private:
    glm::vec4 color;
};


#endif //INC_2DSDL_WIREOBJECT_H
