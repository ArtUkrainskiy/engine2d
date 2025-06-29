//
// Created by artem on 07.05.24.
//

#ifndef INC_2DSDL_OBJECTTRANSFORM_H
#define INC_2DSDL_OBJECTTRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ObjectTransform {
public:
    ObjectTransform(const glm::vec2 position, const glm::vec2 size)
            : position(position), size(size), angle(0.0f), scale(1.0f), 
              transformDirty(true), centerDirty(true) {
    }

    void setSize(const glm::vec2& newSize) {
        if (size != newSize) {
            size = newSize;
            markDirty();
        }
    }

    void setPosition(const glm::vec2& newPosition) {
        if (position != newPosition) {
            position = newPosition;
            markDirty();
        }
    }

    const glm::vec2& getPosition() const {
        return position;
    }

    const glm::vec2& getSize() const {
        return size;
    }

    void translatePosition(const glm::vec2& delta) {
        if (delta.x != 0.0f || delta.y != 0.0f) {
            position += delta;
            markDirty();
        }
    }

    void setAngle(float rotationAngle) {
        if (angle != rotationAngle) {
            angle = rotationAngle;
            transformDirty = true;
        }
    }

    float getAngle() const {
        return angle;
    }

    void setScale(float newScale) {
        if (scale != newScale) {
            scale = newScale;
            transformDirty = true;
        }
    }

    float getScale() const {
        return scale;
    }

    // Lazy evaluation - only calculate when needed
    const glm::mat4& getModelMatrix() const {
        if (transformDirty) {
            updateTransformMatrix();
        }
        return transformMatrix;
    }

    // Cached center calculation
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

    // Batch update multiple properties efficiently
    void setTransform(const glm::vec2& newPosition, float newAngle, float newScale) {
        bool needsUpdate = false;
        
        if (position != newPosition) {
            position = newPosition;
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

    // Check if transform has changed since last matrix calculation
    bool isDirty() const {
        return transformDirty;
    }

    static glm::vec2 extractPosition(const glm::mat4& transform) {
        return {transform[3][0], transform[3][1]};
    }

protected:
    glm::vec2 position;
    glm::vec2 size;
    float angle;
    float scale;

    // Cached data with dirty flags
    mutable glm::mat4 transformMatrix{};
    mutable glm::vec2 cachedCenter{};
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

#endif //INC_2DSDL_OBJECTTRANSFORM_H
