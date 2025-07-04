#include "graphics/VertexArrayObject.h"
#include <iostream>

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &vao);
    if (vao == 0) {
        std::cerr << "Error: Failed to generate VAO" << std::endl;
    }
}

VertexArrayObject::~VertexArrayObject() {
    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
    }
    for (auto& pair : buffers) {
        if (pair.second != 0) {
            glDeleteBuffers(1, &pair.second);
        }
    }
}

bool VertexArrayObject::createBuffer(uint64_t id, const void *data, size_t size, uint64_t divisor) {
    // Allow nullptr data for buffer initialization
    if (data && size == 0) {
        std::cerr << "Error: Invalid buffer data" << std::endl;
        return false;
    }

    glBindVertexArray(vao);

    if (buffers.find(id) == buffers.end()) {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        if (buffer == 0) {
            std::cerr << "Error: Failed to generate buffer" << std::endl;
            return false;
        }
        buffers[id] = buffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[id]);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in createBuffer: " << error << std::endl;
        return false;
    }

    glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glVertexAttribDivisor(id, divisor);
    glEnableVertexAttribArray(id);

    return true;
}

bool VertexArrayObject::createInterleavedBuffer(const void *data, size_t size) {
    if (!data || size == 0) {
        std::cerr << "Warning: Empty interleaved buffer data" << std::endl;
        return true; // Allow empty buffers for initialization
    }

    glBindVertexArray(vao);

    if (buffers.find(VERTEX_BUFFER) == buffers.end()) {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        if (buffer == 0) {
            std::cerr << "Error: Failed to generate interleaved buffer" << std::endl;
            return false;
        }
        buffers[VERTEX_BUFFER] = buffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTEX_BUFFER]);
    
    // Use GL_STREAM_DRAW for better performance with frequently updated data
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in createInterleavedBuffer: " << error << std::endl;
        return false;
    }

    // Setup interleaved attributes: position (2) + color (4) = 6 floats per vertex
    size_t stride = 6 * sizeof(float);
    
    // Position attribute (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    
    // Color attribute (location 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));

    return true;
}

bool VertexArrayObject::createSimpleInstanceBuffer(const void *data, size_t size) {
    if (!data || size == 0) {
        std::cerr << "Error: Invalid simple instance buffer data" << std::endl;
        return false;
    }

    glBindVertexArray(vao);

    if (buffers.find(INSTANCE_BUFFER) == buffers.end()) {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        if (buffer == 0) {
            std::cerr << "Error: Failed to generate simple instance buffer" << std::endl;
            return false;
        }
        buffers[INSTANCE_BUFFER] = buffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[INSTANCE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in createSimpleInstanceBuffer: " << error << std::endl;
        return false;
    }

    size_t stride = 2 * sizeof(float); // Only position
    
    // Position (location 1) - vec2
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribDivisor(1, 1);

    return true;
}

bool VertexArrayObject::createInstance2DBuffer(const void *data, size_t size) {
    if (!data || size == 0) {
        std::cerr << "Error: Invalid 2D instance buffer data" << std::endl;
        return false;
    }

    glBindVertexArray(vao);

    if (buffers.find(INSTANCE_BUFFER) == buffers.end()) {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        if (buffer == 0) {
            std::cerr << "Error: Failed to generate 2D instance buffer" << std::endl;
            return false;
        }
        buffers[INSTANCE_BUFFER] = buffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[INSTANCE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in createInstance2DBuffer: " << error << std::endl;
        return false;
    }

    size_t stride = 9 * sizeof(float); // InstanceData2D size
    
    // Position (location 1) - vec2
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribDivisor(1, 1);
    
    // Size (location 2) - vec2  
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glVertexAttribDivisor(2, 1);
    
    // Rotation (location 3) - float
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, stride, (void*)(4 * sizeof(float)));
    glVertexAttribDivisor(3, 1);
    
    // Color (location 4) - vec4
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    glVertexAttribDivisor(4, 1);

    return true;
}

bool VertexArrayObject::createInstanceBuffer(const void *data, size_t size) {
    if (!data || size == 0) {
        std::cerr << "Error: Invalid instance buffer data" << std::endl;
        return false;
    }

    glBindVertexArray(vao);

    if (buffers.find(INSTANCE_BUFFER) == buffers.end()) {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        if (buffer == 0) {
            std::cerr << "Error: Failed to generate instance buffer" << std::endl;
            return false;
        }
        buffers[INSTANCE_BUFFER] = buffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[INSTANCE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in createInstanceBuffer: " << error << std::endl;
        return false;
    }

    // Setup mat4 transform (locations 1,2,3,4)
    size_t stride = sizeof(glm::mat4) + sizeof(glm::vec4); // InstanceData size
    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(1 + i);
        glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, stride, 
                            (void*)(i * sizeof(glm::vec4)));
        glVertexAttribDivisor(1 + i, 1); // Instance divisor
    }

    // Setup vec4 color (location 5)
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, stride, 
                        (void*)(sizeof(glm::mat4)));
    glVertexAttribDivisor(5, 1); // Instance divisor

    return true;
}

bool VertexArrayObject::updateBufferData(uint64_t id, const void *data, size_t size) {
    if (buffers.find(id) == buffers.end()) {
        // Create buffer if it doesn't exist - this is normal
        GLuint buffer;
        glGenBuffers(1, &buffer);
        if (buffer == 0) {
            std::cerr << "Error: Failed to generate buffer for ID " << id << std::endl;
            return false;
        }
        buffers[id] = buffer;
    }

    if (!data || size == 0) {
        std::cerr << "Warning: Empty buffer update data for ID " << id << std::endl;
        return true; // Allow empty updates
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[id]);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // Setup vertex attributes based on buffer type
    if (id == VERTEX_BUFFER) {
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    } else if (id == TEXTURE_BUFFER) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
    }

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in updateBufferData: " << error << std::endl;
        return false;
    }

    return true;
}

void VertexArrayObject::bind() const {
    if (vao == 0) {
        std::cerr << "Warning: Attempting to bind invalid VAO" << std::endl;
        return;
    }
    glBindVertexArray(vao);
}

void VertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

void VertexArrayObject::draw(GLenum mode, GLsizei instances) const {
    if (instances <= 0) {
        std::cerr << "Warning: Invalid instance count: " << instances << std::endl;
        return;
    }
    
    bind();
    glDrawArraysInstanced(mode, 0, 6, instances);
    
    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL error in draw: " << error << std::endl;
    }
}

GLuint VertexArrayObject::getBuffer(uint64_t id) const {
    auto it = buffers.find(id);
    return (it != buffers.end()) ? it->second : 0;
}