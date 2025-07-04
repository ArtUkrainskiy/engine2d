#ifndef INC_2DSDL_VERTEXARRAYOBJECT_H
#define INC_2DSDL_VERTEXARRAYOBJECT_H

#include <unordered_map>
#include <GLES3/gl3.h>
#include <glm/matrix.hpp>


class VertexArrayObject {
public:
    enum BufferType {
        VERTEX_BUFFER = 0,
        TEXTURE_BUFFER,
        INSTANCE_BUFFER
    };

    VertexArrayObject();

    ~VertexArrayObject();

    bool createBuffer(uint64_t id, const void *data, size_t size, uint64_t divisor = 0);

    // Method for interleaved vertex data (position + color)
    bool createInterleavedBuffer(const void *data, size_t size);

    // Simple instance buffer with only positions for testing
    bool createSimpleInstanceBuffer(const void *data, size_t size);

    // Optimized 2D instance buffer: position(2) + size(2) + rotation(1) + color(4) = 9 floats
    bool createInstance2DBuffer(const void *data, size_t size);

    // Legacy method for mat4 + vec4 instances
    bool createInstanceBuffer(const void *data, size_t size);

    bool updateBufferData(uint64_t id, const void *data, size_t size);

    void bind() const;

    void unbind() const;

    void draw(GLenum mode = GL_TRIANGLES, GLsizei instances = 1) const;

    GLuint getBuffer(uint64_t id) const;

    GLuint vao{};

private:
    std::unordered_map<uint64_t, GLuint> buffers;
};


#endif //INC_2DSDL_VERTEXARRAYOBJECT_H
