#include "graphics/Object.h"

#include <core/Camera.h>
#include <core/ServiceProvider.h>

Object::Object(glm::vec2 position, glm::vec2 size, const std::shared_ptr<Shader> &shader) :
        transform(position, size), shader(shader), bufferDirty(true) {
    vao = std::make_shared<VertexArrayObject>();

    // Don't initialize buffers here - they will be created on demand
    // recalculateBuffer();
}

void Object::setName(const std::string &objectName) {
    name = objectName;
}

std::string Object::getName() {
    return name;
}

void Object::setCenterPosition(const glm::vec2& center) {
    transform.setCenterPosition(center);
    markBufferDirty();
}

void Object::setPosition(const glm::vec2& newPosition) {
    transform.setPosition(newPosition);
    markBufferDirty();
}

void Object::setSize(const glm::vec2& newSize) {
    transform.setSize(newSize);
    markBufferDirty();
}

void Object::setAngle(float rotationAngle) {
    transform.setAngle(rotationAngle);
    markBufferDirty();
}

void Object::setScale(float newScale) {
    transform.setScale(newScale);
    markBufferDirty();
}

void Object::translate(const glm::vec2& delta) {
    transform.translate(delta);
    markBufferDirty();
}

const glm::vec2& Object::getPosition() const { 
    return transform.getPosition(); 
}

const glm::vec2& Object::getSize() const { 
    return transform.getSize(); 
}

float Object::getAngle() const { 
    return transform.getAngle(); 
}

float Object::getScale() const { 
    return transform.getScale(); 
}

const glm::vec2& Object::getCenterPosition() const { 
    return transform.getCenterPosition(); 
}

Transform& Object::getTransform() { 
    return transform; 
}

const Transform& Object::getTransform() const { 
    return transform; 
}

void Object::setCollisionLayer(uint32_t layer) { 
    collisionLayer = layer; 
}

void Object::setCollisionMask(uint32_t mask) { 
    collisionMask = mask; 
}

uint32_t Object::getCollisionLayer() const { 
    return collisionLayer; 
}

uint32_t Object::getCollisionMask() const { 
    return collisionMask; 
}

bool Object::canCollideWith(const Object* other) const {
    return (collisionMask & other->collisionLayer) != 0;
}

void Object::addChild(const std::shared_ptr<Object> &child) {
    child->setCenterPosition(this->getCenterPosition());
    childs.push_back(child);
}

void Object::draw() {
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
    
    vao->draw();
    for (const auto &item: childs) {
        item->draw();
    }
}

void Object::recalculateBuffer() {
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

void Object::markBufferDirty() {
    bufferDirty = true;
}