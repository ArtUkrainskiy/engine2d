//
// Modern Transform System - Optimized for Performance
//

#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

/**
 * High-performance transform component with lazy evaluation
 * Suitable for both single objects and batch rendering systems
 */
class Transform {
public:
    Transform(const glm::vec2& position = glm::vec2(0.0f), 
              const glm::vec2& size = glm::vec2(1.0f),
              float angle = 0.0f,
              float scale = 1.0f)
        : position(position), size(size), angle(angle), scale(scale),
          transformDirty(true), centerDirty(true) {
    }

    // === Position ===
    void setPosition(const glm::vec2& newPosition) {
        if (position != newPosition) {
            position = newPosition;
            markDirty();
        }
    }

    const glm::vec2& getPosition() const { return position; }

    void translate(const glm::vec2& delta) {
        if (delta.x != 0.0f || delta.y != 0.0f) {
            position += delta;
            markDirty();
        }
    }

    // === Size ===
    void setSize(const glm::vec2& newSize) {
        if (size != newSize) {
            size = newSize;
            markDirty();
        }
    }

    const glm::vec2& getSize() const { return size; }

    void scaleSize(const glm::vec2& factor) {
        if (factor.x != 1.0f || factor.y != 1.0f) {
            size *= factor;
            markDirty();
        }
    }

    // === Rotation ===
    void setAngle(float newAngle) {
        if (angle != newAngle) {
            angle = newAngle;
            transformDirty = true;
        }
    }

    float getAngle() const { return angle; }

    void rotate(float deltaAngle) {
        if (deltaAngle != 0.0f) {
            angle += deltaAngle;
            transformDirty = true;
        }
    }

    // === Scale ===
    void setScale(float newScale) {
        if (scale != newScale) {
            scale = newScale;
            transformDirty = true;
        }
    }

    float getScale() const { return scale; }

    // === Center Position ===
    const glm::vec2& getCenterPosition() const {
        if (centerDirty) {
            cachedCenter = position + 0.5f * size;
            centerDirty = false;
        }
        return cachedCenter;
    }

    void setCenterPosition(const glm::vec2& center) {
        setPosition(center - 0.5f * size);
    }

    // === Matrix Access ===
    const glm::mat4& getModelMatrix() const {
        if (transformDirty) {
            updateTransformMatrix();
        }
        return transformMatrix;
    }

    // === Batch Operations ===
    void setTransform(const glm::vec2& newPosition, 
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
    bool isDirty() const { return transformDirty; }
    
    void markClean() const { 
        transformDirty = false; 
        centerDirty = false;
    }

    // === Utility ===
    glm::vec2 getBounds() const { return position + size; }
    
    bool contains(const glm::vec2& point) const {
        return point.x >= position.x && point.x <= position.x + size.x &&
               point.y >= position.y && point.y <= position.y + size.y;
    }

    // === Static Utilities ===
    static glm::vec2 extractPosition(const glm::mat4& matrix) {
        return glm::vec2(matrix[3][0], matrix[3][1]);
    }

    static Transform lerp(const Transform& a, const Transform& b, float t) {
        Transform result;
        result.position = glm::mix(a.position, b.position, t);
        result.size = glm::mix(a.size, b.size, t);
        result.angle = glm::mix(a.angle, b.angle, t);
        result.scale = glm::mix(a.scale, b.scale, t);
        result.markDirty();
        return result;
    }

private:
    // Transform data
    glm::vec2 position;
    glm::vec2 size;
    float angle;
    float scale;

    // Cached data with dirty flags
    mutable glm::mat4 transformMatrix{1.0f};
    mutable glm::vec2 cachedCenter{0.0f};
    mutable bool transformDirty;
    mutable bool centerDirty;

    void markDirty() {
        transformDirty = true;
        centerDirty = true;
    }

    void updateTransformMatrix() const {
        const glm::vec2& center = getCenterPosition();

        transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(center, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
        transformMatrix = glm::scale(transformMatrix, glm::vec3(scale, scale, 1.0f));
        transformMatrix = glm::translate(transformMatrix, glm::vec3(-center, 0.0f));
        
        transformDirty = false;
    }
};

/**
 * Transform manager for batch operations and optimizations
 */
class TransformManager {
public:
    static TransformManager& instance() {
        static TransformManager inst;
        return inst;
    }

    // Batch update multiple transforms
    void updateAll(std::vector<Transform*>& transforms) {
        for (auto* transform : transforms) {
            if (transform && transform->isDirty()) {
                // Force matrix calculation
                transform->getModelMatrix();
            }
        }
    }

    // Performance statistics
    size_t getDirtyCount(const std::vector<Transform*>& transforms) const {
        size_t count = 0;
        for (const auto* transform : transforms) {
            if (transform && transform->isDirty()) {
                count++;
            }
        }
        return count;
    }
};

#endif // CORE_TRANSFORM_H