//
// Camera System - Projection Matrix Management
//

#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

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

    Camera(glm::vec2 windowSize, ProjectionType type = ProjectionType::ORTHOGRAPHIC)
        : windowSize(windowSize), projectionType(type), dirty(true) {
        updateProjectionMatrix();
    }

    // Projection matrix access
    glm::mat4 getProjectionMatrix() const {
        if (dirty) {
            updateProjectionMatrix();
            dirty = false;
        }
        return projectionMatrix;
    }

    // Window size management
    void setWindowSize(glm::vec2 size) {
        if (windowSize != size) {
            windowSize = size;
            dirty = true;
        }
    }

    glm::vec2 getWindowSize() const { return windowSize; }

    // View matrix (for 2D scrolling, zoom etc.)
    void setViewPosition(glm::vec2 pos) {
        if (viewPosition != pos) {
            viewPosition = pos;
            viewDirty = true;
        }
    }

    void setZoom(float z) {
        if (zoom != z) {
            zoom = z;
            viewDirty = true;
        }
    }

    glm::mat4 getViewMatrix() const {
        if (viewDirty) {
            updateViewMatrix();
            viewDirty = false;
        }
        return viewMatrix;
    }

    // Combined view-projection matrix
    glm::mat4 getViewProjectionMatrix() const {
        return getProjectionMatrix() * getViewMatrix();
    }

    // Screen-to-world coordinate conversion
    glm::vec2 screenToWorld(glm::vec2 screenPos) const {
        // Convert screen coordinates to world coordinates
        glm::vec4 viewport(0, 0, windowSize.x, windowSize.y);
        glm::mat4 vp = getViewProjectionMatrix();
        
        // Normalize screen coordinates
        glm::vec3 normalized(
            (screenPos.x / windowSize.x) * 2.0f - 1.0f,
            1.0f - (screenPos.y / windowSize.y) * 2.0f,  // Flip Y
            0.0f
        );
        
        glm::vec4 worldPos = glm::inverse(vp) * glm::vec4(normalized, 1.0f);
        return glm::vec2(worldPos.x, worldPos.y);
    }

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

    void updateProjectionMatrix() const {
        switch (projectionType) {
            case ProjectionType::ORTHOGRAPHIC:
                projectionMatrix = glm::ortho(0.0f, windowSize.x, windowSize.y, 0.0f, -1.0f, 1.0f);
                break;
            case ProjectionType::PERSPECTIVE:
                projectionMatrix = glm::perspective(
                    glm::radians(45.0f), 
                    windowSize.x / windowSize.y, 
                    0.1f, 
                    100.0f
                );
                break;
        }
    }

    void updateViewMatrix() const {
        viewMatrix = glm::mat4(1.0f);
        viewMatrix = glm::scale(viewMatrix, glm::vec3(zoom, zoom, 1.0f));
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-viewPosition, 0.0f));
    }
};

/**
 * Global camera singleton for easy access
 */
class CameraManager {
public:
    static void initialize(glm::vec2 windowSize) {
        instance = std::make_unique<Camera>(windowSize);
    }

    static Camera* get() {
        return instance.get();
    }

    static void updateWindowSize(glm::vec2 size) {
        if (instance) {
            instance->setWindowSize(size);
        }
    }

private:
    static std::unique_ptr<Camera> instance;
};

#endif // CORE_CAMERA_H