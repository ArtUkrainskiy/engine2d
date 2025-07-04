#include "InstancedBatchObject.h"
#include <algorithm>
#include <iostream>
#include <core/Camera.h>
#include <core/ServiceProvider.h>

#include "WireObject.h"

InstancedBatchObject::InstancedBatchObject(const std::shared_ptr<Shader>& shader) 
    : Object({0, 0}, {0, 0}, shader), shader(shader), instancesDirty(true), quadSetup(false), vaoInitialized(false) {
    if (!shader) {
        std::cerr << "Error: InstancedBatchObject created with null shader" << std::endl;
    }
    // Don't create VAO in constructor - OpenGL context might not be ready
}

void InstancedBatchObject::addObject(const std::shared_ptr<Object>& object) {
    if (!object) {
        std::cerr << "Warning: Attempting to add null object to instanced batch" << std::endl;
        return;
    }
    objects.push_back(object);
    instancesDirty = true;
}

void InstancedBatchObject::removeObject(const std::shared_ptr<Object>& object) {
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
        instancesDirty = true;
    }
}

void InstancedBatchObject::clear() {
    objects.clear();
    instancesDirty = true;
}

void InstancedBatchObject::buildInstances() {
    if (!instancesDirty) return;

    instanceData.clear();
    instanceData.reserve(objects.size());

    for (const auto& obj : objects) {
        if (!obj) {
            std::cerr << "Warning: Null object in instanced batch, skipping" << std::endl;
            continue;
        }
        
        InstanceData2D data;
        
        // Position (center of object)
        data.position = obj->getPosition() + obj->getSize() * 0.5f;
        
        // Size
        data.size = obj->getSize();
        
        // Rotation
        data.rotation = glm::radians(obj->getAngle());
        
        // Color
        if (auto wireObj = std::dynamic_pointer_cast<WireObject>(obj)) {
            data.color = wireObj->getColor();
        } else {
            data.color = glm::vec4(1.0f, 1.0f, 1.0f, 0.3f);
        }
        
        instanceData.push_back(data);
    }

    // Update instance buffer - use simple position-only for testing
    if (!instanceData.empty() && vao) {
        std::cout << "Creating instance buffer with " << instanceData.size() << " instances" << std::endl;
        std::cout << "First instance: pos(" << instanceData[0].position.x << "," << instanceData[0].position.y 
                  << ") size(" << instanceData[0].size.x << "," << instanceData[0].size.y 
                  << ") rot(" << instanceData[0].rotation << ")" << std::endl;
        
        // Create simple position-only buffer for testing
        std::vector<glm::vec2> simplePositions;
        simplePositions.reserve(instanceData.size());
        for (const auto& data : instanceData) {
            simplePositions.push_back(data.position);
        }
        
        vao->createSimpleInstanceBuffer(simplePositions.data(), 
                                      simplePositions.size() * sizeof(glm::vec2));
        
        // Check for OpenGL errors after buffer creation
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error after creating instance buffer: " << error << std::endl;
        } else {
            std::cout << "Instance buffer created successfully" << std::endl;
        }
    }

    instancesDirty = false;
}

void InstancedBatchObject::draw() {
    if (objects.empty()) return;

    // Initialize VAO on first draw when OpenGL context is ready
    if (!vaoInitialized) {
        vao = std::make_shared<VertexArrayObject>();
        vaoInitialized = true;
        std::cout << "VAO initialized during first draw" << std::endl;
    }

    // Setup unit quad on first draw when OpenGL context is ready
    if (!quadSetup) {
        setupUnitQuad();
        quadSetup = true;
    }

    if (instancesDirty) {
        buildInstances();
    }

    if (!shader) {
        std::cout << "ERROR: Shader is null!" << std::endl;
        return;
    }
    
    // Check if shader loaded successfully before using it
    std::cout << "Activating shader..." << std::endl;
    shader->setActive();
    
    // Check if shader is valid
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL error after shader activation: " << error << std::endl;
        return;
    }
    std::cout << "Shader activated successfully" << std::endl;

    // Set camera matrices
    if (const auto camera = ServiceProvider::get<Camera>()) {
        shader->setUniform("projection", camera->getProjectionMatrix());
        shader->setUniform("view", camera->getViewMatrix());
    } else {
        std::cout << "ERROR: Camera is null!" << std::endl;
        return;
    }

    if (!vao) {
        std::cerr << "Error: VAO is null in draw()" << std::endl;
        return;
    }

    vao->bind();
    
    // Check OpenGL errors before draw
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL error before instanced draw: " << error << std::endl;
        return;
    }

    if (!instanceData.empty()) {
        std::cout << "About to draw " << instanceData.size() << " instances..." << std::endl;
        
        // Debug: Check vertex attribute state
        GLint enabled0, enabled1;
        glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled0);
        glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled1);
        std::cout << "Vertex attribute 0 enabled: " << enabled0 << std::endl;
        std::cout << "Vertex attribute 1 enabled: " << enabled1 << std::endl;
        
        if (!enabled0) {
            std::cout << "ERROR: Vertex attribute 0 (base position) is not enabled!" << std::endl;
            return;
        }
        
        if (!enabled1) {
            std::cout << "ERROR: Vertex attribute 1 (instance position) is not enabled!" << std::endl;
            return;
        }
        
        // Try simple draw first to test if basic VAO works
        std::cout << "Testing simple draw..." << std::endl;
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error after simple draw: " << error << std::endl;
            return;
        }
        std::cout << "Simple draw succeeded, now trying instanced..." << std::endl;
        
        // Try with just 1 instance first
        std::cout << "Trying with 1 instance..." << std::endl;
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1);
        
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error with 1 instance: " << error << std::endl;
            return;
        }
        std::cout << "1 instance worked, trying with all " << instanceData.size() << " instances..." << std::endl;
        
        // Single instanced draw call for all objects!
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, static_cast<GLsizei>(instanceData.size()));
        
        // Check for errors after draw
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL error after instanced draw: " << error << std::endl;
        } else {
            std::cout << "Instanced draw succeeded!" << std::endl;
        }
    }
}

size_t InstancedBatchObject::getObjectCount() const {
    return objects.size();
}

bool InstancedBatchObject::isEmpty() const {
    return objects.empty();
}

void InstancedBatchObject::makeDirty() {
    instancesDirty = true;
}

void InstancedBatchObject::setupUnitQuad() {
    // Unit quad vertices (0 to 1) - will be transformed by instance data
    static const float quadVertices[] = {
        // Triangle 1
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        
        // Triangle 2
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f,  // Top-left
        0.0f, 0.0f   // Bottom-left
    };
    
    std::cout << "Setting up unit quad..." << std::endl;
    
    if (!vao) {
        std::cerr << "Error: VAO is null in setupUnitQuad()" << std::endl;
        return;
    }
    
    // Use VertexArrayObject's createBuffer method - it will set up attribute 0 properly
    bool success = vao->createBuffer(0, quadVertices, sizeof(quadVertices), 0);
    
    if (success) {
        std::cout << "Unit quad setup complete" << std::endl;
    } else {
        std::cout << "Unit quad setup failed!" << std::endl;
    }
}