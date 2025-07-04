#ifndef INC_2DSDL_OBJECT_H
#define INC_2DSDL_OBJECT_H


#include <cstdint>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "Shader.h"
#include "VertexArrayObject.h"
#include "../core/Transform.h"

class Object {
public:
    virtual ~Object() = default;

    Object(glm::vec2 position, glm::vec2 size, const std::shared_ptr<Shader> &shader);

    void setName(const std::string &objectName);

    std::string getName();

    // Transform delegation with buffer dirty marking
    void setCenterPosition(const glm::vec2& center);

    void setPosition(const glm::vec2& newPosition);

    void setSize(const glm::vec2& newSize);

    void setAngle(float rotationAngle);

    void setScale(float newScale);

    void translate(const glm::vec2& delta);

    // Transform getters
    const glm::vec2& getPosition() const;
    const glm::vec2& getSize() const;
    float getAngle() const;
    float getScale() const;
    const glm::vec2& getCenterPosition() const;

    // Access to transform for advanced operations
    Transform& getTransform();
    const Transform& getTransform() const;

    // Collision system
    void setCollisionLayer(uint32_t layer);
    void setCollisionMask(uint32_t mask);
    uint32_t getCollisionLayer() const;
    uint32_t getCollisionMask() const;
    bool canCollideWith(const Object* other) const;


    virtual void addChild(const std::shared_ptr<Object> &child);

    virtual void draw();

    virtual void recalculateBuffer();

protected:
    Transform transform;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexArrayObject> vao;

    std::string name;
    bool bufferDirty;

    // Collision system
    uint32_t collisionLayer = 0;
    uint32_t collisionMask = 0;

    std::vector<std::shared_ptr<Object>> childs;

    void markBufferDirty();
};


#endif //INC_2DSDL_OBJECT_H
