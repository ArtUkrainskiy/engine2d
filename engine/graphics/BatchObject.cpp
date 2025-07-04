#include "BatchObject.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <core/Camera.h>
#include <core/ServiceProvider.h>
#include <GL/glew.h>

#include "WireObject.h"

BatchObject::BatchObject(const std::shared_ptr<Shader>& shader) 
    : Object({0, 0}, {0, 0}, shader), shader(shader), batchDirty(true) {
    if (!shader) {
        std::cerr << "Error: BatchObject created with null shader" << std::endl;
        return;
    }
    vao = std::make_shared<VertexArrayObject>();
}

void BatchObject::addObject(const std::shared_ptr<Object>& object) {
    if (!object) {
        std::cerr << "Warning: Attempting to add null object to batch" << std::endl;
        return;
    }
    objects.push_back(object);
    batchDirty = true;
}

void BatchObject::removeObject(const std::shared_ptr<Object>& object) {
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
        batchDirty = true;
    }
}

void BatchObject::clear() {
    objects.clear();
    batchDirty = true;
}

void BatchObject::buildBatch() {
    if (!batchDirty) return;
    
    // Clear the cached vertices to force rebuild
    cachedBatchVertices.clear();
    
    batchDirty = false;
}

void BatchObject::draw() {
    if (objects.empty()) return;

    if (batchDirty) {
        buildBatch();
    }

    // We use batch rendering approach, not instance data
    if (!shader) {
        std::cerr << "Error: BatchObject shader is null" << std::endl;
        return;
    }

    shader->setActive();

    // Set camera matrices
    if (const auto camera = ServiceProvider::get<Camera>()) {
        shader->setUniform("projection", camera->getProjectionMatrix());
        shader->setUniform("view", camera->getViewMatrix());
        shader->setUniform("model", glm::mat4(1.0f)); // Identity for batch rendering
    } else {
        std::cerr << "Warning: No camera available for BatchObject rendering" << std::endl;
    }
    
    // No need for "col" uniform in vertex color shader

    vao->bind();
    
    // Check OpenGL errors before draw
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL error before draw: " << error << std::endl;
        return;
    }
    
    // Use cached batch vertices if they exist
    if (cachedBatchVertices.empty()) {
        cachedBatchVertices.clear();
        cachedBatchVertices.reserve(objects.size() * 6 * 6); // Pre-allocate memory
        
        for (const auto& obj : objects) {
            if (!obj) {
                std::cerr << "Warning: Null object in batch, skipping" << std::endl;
                continue;
            }
            
            const glm::vec2& pos = obj->getPosition();
            const glm::vec2& size = obj->getSize();
            float angle = glm::radians(obj->getAngle());
            
            // Get object color
            glm::vec4 color;
            if (auto wireObj = std::dynamic_pointer_cast<WireObject>(obj)) {
                color = wireObj->getColor();
            } else {
                color = glm::vec4(1.0f, 1.0f, 1.0f, 0.3f);
            }
            
            // Pre-calculate sin/cos for rotation
            float cos_a = cos(angle);
            float sin_a = sin(angle);
            
            // Calculate corners relative to center for better precision
            float half_w = size.x * 0.5f;
            float half_h = size.y * 0.5f;
            
            // Pre-calculate rotated half-extents
            float rot_x = half_w * cos_a - half_h * sin_a;
            float rot_y = half_w * sin_a + half_h * cos_a;
            float rot_x2 = half_w * cos_a + half_h * sin_a;
            float rot_y2 = half_w * sin_a - half_h * cos_a;
            
            glm::vec2 center = pos + size * 0.5f;
            
            // 6 vertices for quad (2 triangles) - optimized calculation
            std::array<glm::vec2, 6> vertices = {
                glm::vec2(center.x - rot_x, center.y - rot_y),   // Bottom-left
                glm::vec2(center.x + rot_x2, center.y + rot_y2), // Bottom-right  
                glm::vec2(center.x - rot_x2, center.y - rot_y2), // Top-left
                
                glm::vec2(center.x + rot_x2, center.y + rot_y2), // Bottom-right
                glm::vec2(center.x + rot_x, center.y + rot_y),   // Top-right
                glm::vec2(center.x - rot_x2, center.y - rot_y2)  // Top-left
            };
            
            // Add vertex data: position (2) + color (4) = 6 floats per vertex
            for (const auto& vertex : vertices) {
                cachedBatchVertices.insert(cachedBatchVertices.end(), {
                    vertex.x, vertex.y, color.r, color.g, color.b, color.a
                });
            }
        }
        
        // Create vertex buffer with cached data
        if (!cachedBatchVertices.empty()) {
            vao->createInterleavedBuffer(cachedBatchVertices.data(), 
                                       cachedBatchVertices.size() * sizeof(float));
        }
    }
    
    if (!cachedBatchVertices.empty()) {
        // Single draw call for all objects! (using cached data)
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(cachedBatchVertices.size() / 6)); // 6 floats per vertex
    }
}

size_t BatchObject::getObjectCount() const {
    return objects.size();
}

bool BatchObject::isEmpty() const {
    return objects.empty();
}

void BatchObject::makeDirty() {
    batchDirty = true;
    cachedBatchVertices.clear(); // Clear cache when dirty
}