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
    WireObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color);

    void setColor(const glm::vec4& newColor) {
        color = newColor;
    }

    void draw() override;
    void recalculateBuffer() override;

private:
    glm::vec4 color;
    static const float UNIT_QUAD_VERTICES[16];
    
    void initializeBuffers();
};


#endif //INC_2DSDL_WIREOBJECT_H
