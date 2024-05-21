//
// Created by artem on 27.04.24.
//

#ifndef INC_2DSDL_OBJECT_H
#define INC_2DSDL_OBJECT_H


#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "VertexArrayObject.h"
#include "Shader.h"
#include "../math/ObjectTransform.h"

class Object {
public:
    Object(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader) :
            position(pos), size(size), shader(shader) {
        vao = std::make_shared<VertexArrayObject>();

        transform = std::make_shared<ObjectTransform>(position, size);

        vao->createBuffer(vao->VERTEX_BUFFER, nullptr, 0);
        vao->createBuffer(vao->TEXTURE_BUFFER, nullptr, 0);
        vao->createBuffer(vao->INSTANCE_BUFFER, nullptr, 0);
        recalculateBuffer();

    }

    void setName(std::string objectName){
        name = objectName;
    }

    std::string getName(){
        return name;
    }

    void linkPosition(const std::shared_ptr<Object> &object) {
        linkedPosition = &object->position;
    }

    void setPosition(glm::vec2 pos) {
        transform->setPosition(pos);
        position = pos;
        recalculateBuffer();
    }

    void setCenterPosition(glm::vec2 center) {
        position = center - size / 2.f;
        transform->setPosition(position);
        recalculateBuffer();
    }

    glm::vec2 getCenterPosition(){
        return position + size / 2.f;
    }

    void movePosition(glm::vec2 offset) {
        for (const auto &item: childs){
            item->movePosition(offset);
        }
        position += offset;
        transform->setPosition(position);
        recalculateBuffer();
    }

    void setSize(glm::vec2 newSize) {
        size = newSize;
        transform->setSize(newSize);
        recalculateBuffer();
    }

    virtual inline glm::vec2 getPosition(){
        return position;
    }

    virtual inline glm::vec2 getSize(){
        return size;
    }

    virtual void addChild(std::shared_ptr<Object> child){
        child->setCenterPosition(this->getCenterPosition());
        childs.push_back(child);
    }

    virtual void setAngle(float_t angle){
        transform->setRotationAngle(transform->getAngle() + angle);
    }

    virtual float getAngle(){
        return transform->getAngle();
    }

    virtual void draw() {
        shader->setActive();
        shader->setUniform("projection", transform->getTransform());
        vao->bind();
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 1);
    };

    ~Object(){

    };

public:
    virtual void recalculateBuffer() {
        if (linkedPosition) {
            position = *linkedPosition;
        }
        float vertexes[] = {
                position.x, position.y,
                position.x + size.x, position.y,
                position.x + size.x, position.y + size.y,
                position.x, position.y + size.y
        };
        vao->updateBufferData(VertexArrayObject::VERTEX_BUFFER, vertexes, 8 * sizeof(float));
    }

    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexArrayObject> vao;

    std::shared_ptr<ObjectTransform> transform;

    std::string name;

    glm::vec2 position;
    glm::vec2 *linkedPosition = nullptr;
    glm::vec2 size;



    std::vector<std::shared_ptr<Object>> childs;
};


#endif //INC_2DSDL_OBJECT_H
