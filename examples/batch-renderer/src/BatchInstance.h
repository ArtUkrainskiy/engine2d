//
// Created by artem.ukrainskiy on 27.06.25.
//

#ifndef INC_2DSDL_BATCHINSTANCE_H
#define INC_2DSDL_BATCHINSTANCE_H

#include <glm/glm.hpp>
#include <memory>

class BatchedObject;

class BatchInstance {
public:
    BatchInstance(BatchedObject* parent, size_t index);

    void setPosition(const glm::vec2& pos);
    void setSize(const glm::vec2& sz);
    void setColor(const glm::vec4& col);

    glm::vec2 getPosition() const { return position; }
    glm::vec2 getSize() const { return size; }
    glm::vec4 getColor() const { return color; }

    size_t getIndex() const { return index; }
    bool isValid() const { return parent != nullptr; }

    void remove();

private:
    BatchedObject* parent;
    size_t index;
    
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;

    friend class BatchedObject;
    void invalidate() { parent = nullptr; }
};

#endif //INC_2DSDL_BATCHINSTANCE_H