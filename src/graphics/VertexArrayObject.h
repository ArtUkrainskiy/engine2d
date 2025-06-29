//
// Created by artem on 21.04.24.
//

#ifndef INC_2DSDL_VERTEXARRAYOBJECT_H
#define INC_2DSDL_VERTEXARRAYOBJECT_H

#include <GLES3/gl3.h>
#include <vector>
#include <iostream>


class VertexArrayObject {
public:
    enum {
        VERTEX_BUFFER = 0,
        TEXTURE_BUFFER,
        INSTANCE_BUFFER
    };

    VertexArrayObject() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &buffers[VERTEX_BUFFER]);
        glGenBuffers(1, &buffers[TEXTURE_BUFFER]);
        glGenBuffers(1, &buffers[INSTANCE_BUFFER]);

    }

    ~VertexArrayObject() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &buffers[VERTEX_BUFFER]);
        glDeleteBuffers(1, &buffers[TEXTURE_BUFFER]);
        glDeleteBuffers(1, &buffers[INSTANCE_BUFFER]);
    }


    bool createBuffer(uint64_t id, const void *data, size_t size, uint64_t divisor = 0) {
        glBindVertexArray(vao);

        // Create and bind the first vertex buffer object
        glBindBuffer(GL_ARRAY_BUFFER, buffers[id]);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        // Specify the vertex attribute pointers
        glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
        glVertexAttribDivisor(id, divisor);
        glEnableVertexAttribArray(id);

        return true;
    }

    bool updateBufferData(uint64_t id, const void *data, size_t size) {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[id]);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        return true;
    }

    void bind() const {
        glBindVertexArray(vao);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    GLuint getBuffer(uint64_t id) const {
        return buffers[id];
    }

    GLuint vao{};

private:
    GLuint buffers[10];
};


#endif //INC_2DSDL_VERTEXARRAYOBJECT_H
