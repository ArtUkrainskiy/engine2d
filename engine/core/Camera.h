#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Manages projection matrix and view transformations
 * Single Responsibility: Camera/View management
 */
class Camera {
public:
    enum class ProjectionType {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    Camera(glm::vec2 windowSize, ProjectionType type = ProjectionType::ORTHOGRAPHIC);

    // Projection matrix access
    glm::mat4 getProjectionMatrix() const;

    // Window size management
    void setWindowSize(glm::vec2 size);

    glm::vec2 getWindowSize() const { return windowSize; }

    // View matrix (for 2D scrolling, zoom etc.)
    void setViewPosition(glm::vec2 pos);

    void setZoom(float z);

    glm::mat4 getViewMatrix() const;

    // Combined view-projection matrix
    glm::mat4 getViewProjectionMatrix() const;

    // Screen-to-world coordinate conversion
    glm::vec2 screenToWorld(glm::vec2 screenPos) const;

private:
    glm::vec2 windowSize;
    ProjectionType projectionType;
    
    // View parameters
    glm::vec2 viewPosition{0.0f, 0.0f};
    float zoom = 1.0f;
    
    // Cached matrices
    mutable glm::mat4 projectionMatrix{1.0f};
    mutable glm::mat4 viewMatrix{1.0f};
    mutable bool dirty = true;
    mutable bool viewDirty = true;

    void updateProjectionMatrix() const;
    void updateViewMatrix() const;
};

/**
 * Global camera singleton for easy access
 */
class CameraManager {
public:
    static void initialize(glm::vec2 windowSize);
    static Camera* get();
    static void updateWindowSize(glm::vec2 size);

private:
    static std::unique_ptr<Camera> instance;
};

#endif // CORE_CAMERA_H