//
// Created by artem on 27.04.24.
//

#ifndef INC_2DSDL_OBJECT_H
#define INC_2DSDL_OBJECT_H


#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "VertexArrayObject.h"
#include "Shader.h"
#include "../core/Transform.h"
#include "../core/ServiceProvider.h"
#include "../core/Camera.h"

class Object {
public:
    Object(glm::vec2 position, glm::vec2 size, const std::shared_ptr<Shader> &shader) :
            transform(position, size), shader(shader), bufferDirty(true) {
        vao = std::make_shared<VertexArrayObject>();

        vao->createBuffer(vao->VERTEX_BUFFER, nullptr, 0);
        vao->createBuffer(vao->TEXTURE_BUFFER, nullptr, 0);
        vao->createBuffer(vao->INSTANCE_BUFFER, nullptr, 0);
        // recalculateBuffer();

    }

    void setName(const std::string &objectName) {
        name = objectName;
    }

    std::string getName() {
        return name;
    }

    // Transform delegation with buffer dirty marking
    void setCenterPosition(const glm::vec2& center) {
        transform.setCenterPosition(center);
        markBufferDirty();
    }

    void setPosition(const glm::vec2& newPosition) {
        transform.setPosition(newPosition);
        markBufferDirty();
    }

    void setSize(const glm::vec2& newSize) {
        transform.setSize(newSize);
        markBufferDirty();
    }

    void setAngle(float rotationAngle) {
        transform.setAngle(rotationAngle);
        markBufferDirty();
    }

    void setScale(float newScale) {
        transform.setScale(newScale);
        markBufferDirty();
    }

    void translate(const glm::vec2& delta) {
        transform.translate(delta);
        markBufferDirty();
    }

    // Transform getters
    const glm::vec2& getPosition() const { return transform.getPosition(); }
    const glm::vec2& getSize() const { return transform.getSize(); }
    float getAngle() const { return transform.getAngle(); }
    float getScale() const { return transform.getScale(); }
    const glm::vec2& getCenterPosition() const { return transform.getCenterPosition(); }

    // Access to transform for advanced operations
    Transform& getTransform() { return transform; }
    const Transform& getTransform() const { return transform; }


    virtual void addChild(const std::shared_ptr<Object> &child) {
        child->setCenterPosition(this->getCenterPosition());
        childs.push_back(child);
    }

    virtual void draw() {
        // Only recalculate buffer if transform changed
        if (transform.isDirty() || bufferDirty) {
            recalculateBuffer();
            bufferDirty = false;
        }

        shader->setActive();
        
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
        
        vao->bind();
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1);
        for (const auto &item: childs) {
            item->draw();
        }
    };

    virtual void recalculateBuffer() {
        const glm::vec2& pos = transform.getPosition();
        const glm::vec2& size = transform.getSize();
        
        float vertexes[] = {
                // Triangle 1: Bottom-left quad triangle
                pos.x, pos.y,                    // Bottom-left
                pos.x + size.x, pos.y,          // Bottom-right  
                pos.x, pos.y + size.y,          // Top-left
                
                // Triangle 2: Top-right quad triangle  
                pos.x + size.x, pos.y,          // Bottom-right
                pos.x + size.x, pos.y + size.y, // Top-right
                pos.x, pos.y + size.y           // Top-left
        };
        vao->updateBufferData(VertexArrayObject::VERTEX_BUFFER, vertexes, 12 * sizeof(float));
    }

protected:
    Transform transform;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexArrayObject> vao;

    std::string name;
    bool bufferDirty;

    std::vector<std::shared_ptr<Object>> childs;

    void markBufferDirty() {
        bufferDirty = true;
    }
};


#endif //INC_2DSDL_OBJECT_H
