//
// Created by artem on 06.05.24.
//

#include "graphics/WireObject.h"


// Line vertices for wireframe rectangle (GL_LINES) - 8 vertices for 4 lines
const float WireObject::UNIT_QUAD_VERTICES[16] = {
    // Bottom edge
    0.0f, 0.0f,  1.0f, 0.0f,
    // Right edge  
    1.0f, 0.0f,  1.0f, 1.0f,
    // Top edge
    1.0f, 1.0f,  0.0f, 1.0f,
    // Left edge
    0.0f, 1.0f,  0.0f, 0.0f
};

WireObject::WireObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color)
    : Object(pos, size, shader), color(color) {
    initializeBuffers();
}

void WireObject::initializeBuffers() {
    if (!vao) {
        vao = std::make_shared<VertexArrayObject>();
    }

    // Create vertex buffer with unit quad
    vao->createBuffer(VertexArrayObject::VERTEX_BUFFER, UNIT_QUAD_VERTICES, sizeof(UNIT_QUAD_VERTICES));

}

void WireObject::draw() {
    if (!vao) {
        initializeBuffers();
    }

    shader->setActive();
    vao->bind();
    shader->setUniform("col", color);

    // Use proper MVP matrices - Transform should scale unit quad to object size
    if (const auto camera = ServiceProvider::get<Camera>()) {
        shader->setUniform("projection", camera->getProjectionMatrix());
        shader->setUniform("view", camera->getViewMatrix());
        
        // Create model matrix: translate to position and scale to size
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(getPosition(), 0.0f));
        model = glm::scale(model, glm::vec3(getSize(), 1.0f));
        shader->setUniform("model", model);
    } else {
        // Fallback: create transform matrix manually
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(getPosition(), 0.0f));
        transform = glm::scale(transform, glm::vec3(getSize(), 1.0f));
        shader->setUniform("projection", transform);
        shader->setUniform("view", glm::mat4(1.0f));
        shader->setUniform("model", glm::mat4(1.0f));
    }

    // Draw wireframe using line vertices (8 vertices = 4 lines)
    glDrawArrays(GL_LINES, 0, 8);

    // Draw children
    for (const auto &child : childs) {
        child->draw();
    }
}

void WireObject::recalculateBuffer() {
    // No need to recalculate - using unit quad with model matrix transform
    // This is more efficient and follows modern OpenGL practices
}
