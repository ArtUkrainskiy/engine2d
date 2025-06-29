//
// Created by artem.ukrainskiy on 27.06.25.
//

#include "BatchedObject.h"
#include <GLES3/gl3.h>
#include <algorithm>

const float BatchedObject::QUAD_VERTICES[VERTICES_PER_QUAD * 2] = {
    // Triangle 1: Bottom-left quad triangle
    0.0f, 0.0f,  // Bottom-left
    1.0f, 0.0f,  // Bottom-right
    0.0f, 1.0f,  // Top-left
    
    // Triangle 2: Top-right quad triangle
    1.0f, 0.0f,  // Bottom-right
    1.0f, 1.0f,  // Top-right
    0.0f, 1.0f   // Top-left
};

BatchedObject::BatchedObject(const std::shared_ptr<Shader>& shader) 
    : shader(shader) {
    setupBuffers();
}

BatchedObject::~BatchedObject() {
    for (auto& ref : instanceRefs) {
        if (auto instance = ref.lock()) {
            instance->invalidate();
        }
    }
}

void BatchedObject::setupBuffers() {
    vao = std::make_shared<VertexArrayObject>();
    
    // Setup vertex buffer with base quad
    vao->createBuffer(VertexArrayObject::VERTEX_BUFFER, QUAD_VERTICES, sizeof(QUAD_VERTICES));
    
    // Setup instance buffer (initially empty)
    vao->createBuffer(VertexArrayObject::INSTANCE_BUFFER, nullptr, 0, 1);
    
    // Setup additional instance attributes
    vao->bind();
    
    // Bind instance buffer for attribute setup
    glBindBuffer(GL_ARRAY_BUFFER, vao->getBuffer(VertexArrayObject::INSTANCE_BUFFER));
    
    // Position attribute (location 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, position));
    glVertexAttribDivisor(2, 1);
    glEnableVertexAttribArray(2);
    
    // Size attribute (location 3)
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, size));
    glVertexAttribDivisor(3, 1);
    glEnableVertexAttribArray(3);
    
    // Color attribute (location 4)
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, color));
    glVertexAttribDivisor(4, 1);
    glEnableVertexAttribArray(4);
}

std::shared_ptr<BatchInstance> BatchedObject::addInstance(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    size_t index;
    
    if (!freeIndices.empty()) {
        index = freeIndices.back();
        freeIndices.pop_back();
        instances[index] = {position, size, color, true};
    } else {
        index = instances.size();
        instances.push_back({position, size, color, true});
        instanceRefs.resize(instances.size());
    }
    
    auto instance = std::make_shared<BatchInstance>(this, index);
    instance->position = position;
    instance->size = size;
    instance->color = color;
    
    instanceRefs[index] = instance;
    bufferDirty = true;
    
    return instance;
}

void BatchedObject::removeInstance(size_t index) {
    if (index >= instances.size() || !instances[index].active) return;
    
    instances[index].active = false;
    freeIndices.push_back(index);
    
    if (auto instance = instanceRefs[index].lock()) {
        instance->invalidate();
    }
    instanceRefs[index].reset();
    
    bufferDirty = true;
}

void BatchedObject::removeInstance(const std::shared_ptr<BatchInstance>& instance) {
    if (!instance || !instance->isValid()) return;
    removeInstance(instance->getIndex());
}

void BatchedObject::updateInstance(size_t index, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    if (index >= instances.size() || !instances[index].active) return;
    
    instances[index].position = position;
    instances[index].size = size;
    instances[index].color = color;
    bufferDirty = true;
}

void BatchedObject::draw() {
    if (instances.empty()) return;
    
    if (bufferDirty) {
        updateInstanceBuffer();
        bufferDirty = false;
    }
    
    shader->setActive();
    shader->setUniform("projection", projectionMatrix);
    
    vao->bind();
    
    size_t activeCount = getActiveInstanceCount();
    if (activeCount > 0) {
        glDrawArraysInstanced(GL_TRIANGLES, 0, VERTICES_PER_QUAD, static_cast<GLsizei>(activeCount));
    }
}

void BatchedObject::setProjectionMatrix(const glm::mat4& projection) {
    projectionMatrix = projection;
}

size_t BatchedObject::getActiveInstanceCount() const {
    return std::count_if(instances.begin(), instances.end(), 
                        [](const InstanceData& data) { return data.active; });
}

void BatchedObject::updateInstanceBuffer() {
    std::vector<InstanceData> activeInstances;
    activeInstances.reserve(getActiveInstanceCount());
    
    for (const auto& instance : instances) {
        if (instance.active) {
            activeInstances.push_back(instance);
        }
    }
    
    if (!activeInstances.empty()) {
        vao->updateBufferData(VertexArrayObject::INSTANCE_BUFFER, 
                             activeInstances.data(), 
                             activeInstances.size() * sizeof(InstanceData));
    }
}