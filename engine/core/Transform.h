#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transform {
public:
    Transform(const glm::vec2& position = glm::vec2(0.0f), 
              const glm::vec2& size = glm::vec2(1.0f),
              float angle = 0.0f,
              float scale = 1.0f);

    // === Position ===
    void setPosition(const glm::vec2& newPosition);
    const glm::vec2& getPosition() const;
    void translate(const glm::vec2& delta);

    // === Size ===
    void setSize(const glm::vec2& newSize);
    const glm::vec2& getSize() const;
    void scaleSize(const glm::vec2& factor);

    // === Rotation ===
    void setAngle(float newAngle);
    float getAngle() const;
    void rotate(float deltaAngle);

    // === Scale ===
    void setScale(float newScale);
    float getScale() const;

    // === Center Position ===
    const glm::vec2& getCenterPosition() const;
    void setCenterPosition(const glm::vec2& center);

    // === Matrix Access ===
    const glm::mat4& getModelMatrix() const;

    // === Batch Operations ===
    void setTransform(const glm::vec2& newPosition, 
                     const glm::vec2& newSize,
                     float newAngle, 
                     float newScale);

    // === State Queries ===
    bool isDirty() const;
    void markClean() const;

    // === Utility ===
    glm::vec2 getBounds() const;
    bool contains(const glm::vec2& point) const;

    // === Static Utilities ===
    static glm::vec2 extractPosition(const glm::mat4& matrix);
    static Transform lerp(const Transform& a, const Transform& b, float t);

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

    void markDirty();
    void updateTransformMatrix() const;
};


class TransformManager {
public:
    static TransformManager& instance();

    // Batch update multiple transforms
    void updateAll(std::vector<Transform*>& transforms);

    // Performance statistics
    size_t getDirtyCount(const std::vector<Transform*>& transforms) const;
};

#endif // CORE_TRANSFORM_H