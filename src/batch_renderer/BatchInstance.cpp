//
// Created by artem.ukrainskiy on 27.06.25.
//

#include "BatchInstance.h"
#include "BatchedObject.h"

BatchInstance::BatchInstance(BatchedObject* parent, size_t index)
    : parent(parent), index(index), position(0.0f), size(1.0f), color(1.0f) {
}

void BatchInstance::setPosition(const glm::vec2& pos) {
    if (!isValid()) return;
    position = pos;
    parent->updateInstance(index, position, size, color);
}

void BatchInstance::setSize(const glm::vec2& sz) {
    if (!isValid()) return;
    size = sz;
    parent->updateInstance(index, position, size, color);
}

void BatchInstance::setColor(const glm::vec4& col) {
    if (!isValid()) return;
    color = col;
    parent->updateInstance(index, position, size, color);
}

void BatchInstance::remove() {
    if (!isValid()) return;
    parent->removeInstance(index);
}