#include "core/Camera.h"
#include <iostream>

std::unique_ptr<Camera> CameraManager::instance = nullptr;

// === Camera Implementation ===

Camera::Camera(glm::vec2 windowSize, ProjectionType type)
    : windowSize(windowSize), projectionType(type), dirty(true) {
    updateProjectionMatrix();
}

glm::mat4 Camera::getProjectionMatrix() const {
    if (dirty) {
        updateProjectionMatrix();
        dirty = false;
    }
    return projectionMatrix;
}

void Camera::setWindowSize(glm::vec2 size) {
    if (windowSize != size) {
        windowSize = size;
        dirty = true;
    }
}

void Camera::setViewPosition(glm::vec2 pos) {
    if (viewPosition != pos) {
        viewPosition = pos;
        viewDirty = true;
    }
}

void Camera::setZoom(float z) {
    if (z <= 0.0f) {
        std::cerr << "Warning: Invalid zoom value " << z << ", using 1.0f instead" << std::endl;
        z = 1.0f;
    }
    if (zoom != z) {
        zoom = z;
        viewDirty = true;
    }
}

glm::mat4 Camera::getViewMatrix() const {
    if (viewDirty) {
        updateViewMatrix();
        viewDirty = false;
    }
    return viewMatrix;
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

glm::vec2 Camera::screenToWorld(glm::vec2 screenPos) const {
    if (windowSize.x <= 0.0f || windowSize.y <= 0.0f) {
        std::cerr << "Error: Invalid window size in screenToWorld conversion" << std::endl;
        return glm::vec2(0.0f);
    }
    
    // Convert screen coordinates to world coordinates
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

void Camera::updateProjectionMatrix() const {
    if (windowSize.x <= 0.0f || windowSize.y <= 0.0f) {
        std::cerr << "Error: Invalid window size for projection matrix" << std::endl;
        projectionMatrix = glm::mat4(1.0f);
        return;
    }
    
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

void Camera::updateViewMatrix() const {
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::scale(viewMatrix, glm::vec3(zoom, zoom, 1.0f));
    viewMatrix = glm::translate(viewMatrix, glm::vec3(-viewPosition, 0.0f));
}

// === CameraManager Implementation ===

void CameraManager::initialize(glm::vec2 windowSize) {
    if (windowSize.x <= 0.0f || windowSize.y <= 0.0f) {
        std::cerr << "Error: Invalid window size for camera initialization" << std::endl;
        return;
    }
    instance = std::make_unique<Camera>(windowSize);
}

Camera* CameraManager::get() {
    if (!instance) {
        std::cerr << "Warning: CameraManager not initialized, returning nullptr" << std::endl;
    }
    return instance.get();
}

void CameraManager::updateWindowSize(glm::vec2 size) {
    if (instance) {
        instance->setWindowSize(size);
    } else {
        std::cerr << "Warning: CameraManager not initialized, cannot update window size" << std::endl;
    }
}