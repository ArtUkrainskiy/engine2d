#include "core/Transform.h"
#include <vector>

// === Transform Class Implementation ===

Transform::Transform(const glm::vec2& position, const glm::vec2& size, float angle, float scale)
    : position(position), size(size), angle(angle), scale(scale),
      transformMatrix(1.0f), cachedCenter(0.0f),
      transformDirty(true), centerDirty(true) {
}

// === Position ===
void Transform::setPosition(const glm::vec2& newPosition) {
    if (position != newPosition) {
        position = newPosition;
        markDirty();
    }
}

const glm::vec2& Transform::getPosition() const {
    return position;
}

void Transform::translate(const glm::vec2& delta) {
    if (delta.x != 0.0f || delta.y != 0.0f) {
        position += delta;
        markDirty();
    }
}

// === Size ===
void Transform::setSize(const glm::vec2& newSize) {
    if (size != newSize) {
        size = newSize;
        markDirty();
    }
}

const glm::vec2& Transform::getSize() const {
    return size;
}

void Transform::scaleSize(const glm::vec2& factor) {
    if (factor.x != 1.0f || factor.y != 1.0f) {
        size *= factor;
        markDirty();
    }
}

// === Rotation ===
void Transform::setAngle(float newAngle) {
    if (angle != newAngle) {
        angle = newAngle;
        transformDirty = true;
    }
}

float Transform::getAngle() const {
    return angle;
}

void Transform::rotate(float deltaAngle) {
    if (deltaAngle != 0.0f) {
        angle += deltaAngle;
        transformDirty = true;
    }
}

// === Scale ===
void Transform::setScale(float newScale) {
    if (scale != newScale) {
        scale = newScale;
        transformDirty = true;
    }
}

float Transform::getScale() const {
    return scale;
}

// === Center Position ===
const glm::vec2& Transform::getCenterPosition() const {
    if (centerDirty) {
        cachedCenter = position + 0.5f * size;
        centerDirty = false;
    }
    return cachedCenter;
}

void Transform::setCenterPosition(const glm::vec2& center) {
    setPosition(center - 0.5f * size);
}

// === Matrix Access ===
const glm::mat4& Transform::getModelMatrix() const {
    if (transformDirty) {
        updateTransformMatrix();
    }
    return transformMatrix;
}

// === Batch Operations ===
void Transform::setTransform(const glm::vec2& newPosition, 
                           const glm::vec2& newSize,
                           float newAngle, 
                           float newScale) {
    bool needsUpdate = false;
    
    if (position != newPosition) {
        position = newPosition;
        needsUpdate = true;
    }
    if (size != newSize) {
        size = newSize;
        needsUpdate = true;
    }
    if (angle != newAngle) {
        angle = newAngle;
        needsUpdate = true;
    }
    if (scale != newScale) {
        scale = newScale;
        needsUpdate = true;
    }
    
    if (needsUpdate) {
        markDirty();
    }
}

// === State Queries ===
bool Transform::isDirty() const {
    return transformDirty;
}

void Transform::markClean() const {
    transformDirty = false;
    centerDirty = false;
}

// === Utility ===
glm::vec2 Transform::getBounds() const {
    return position + size;
}

bool Transform::contains(const glm::vec2& point) const {
    return point.x >= position.x && point.x <= position.x + size.x &&
           point.y >= position.y && point.y <= position.y + size.y;
}

// === Static Utilities ===
glm::vec2 Transform::extractPosition(const glm::mat4& matrix) {
    return glm::vec2(matrix[3][0], matrix[3][1]);
}

Transform Transform::lerp(const Transform& a, const Transform& b, float t) {
    Transform result;
    result.position = glm::mix(a.position, b.position, t);
    result.size = glm::mix(a.size, b.size, t);
    result.angle = glm::mix(a.angle, b.angle, t);
    result.scale = glm::mix(a.scale, b.scale, t);
    result.markDirty();
    return result;
}

// === Private Methods ===
void Transform::markDirty() {
    transformDirty = true;
    centerDirty = true;
}

void Transform::updateTransformMatrix() const {
    const glm::vec2& center = getCenterPosition();

    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(center, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
    transformMatrix = glm::scale(transformMatrix, glm::vec3(scale, scale, 1.0f));
    transformMatrix = glm::translate(transformMatrix, glm::vec3(-center, 0.0f));
    
    transformDirty = false;
}

// === TransformManager Class Implementation ===

TransformManager& TransformManager::instance() {
    static TransformManager inst;
    return inst;
}

void TransformManager::updateAll(std::vector<Transform*>& transforms) {
    for (auto* transform : transforms) {
        if (transform && transform->isDirty()) {
            // Force matrix calculation
            transform->getModelMatrix();
        }
    }
}

size_t TransformManager::getDirtyCount(const std::vector<Transform*>& transforms) const {
    size_t count = 0;
    for (const auto* transform : transforms) {
        if (transform && transform->isDirty()) {
            count++;
        }
    }
    return count;
}