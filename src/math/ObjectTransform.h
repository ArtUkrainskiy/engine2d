//
// Created by artem on 07.05.24.
//

#ifndef INC_2DSDL_OBJECTTRANSFORM_H
#define INC_2DSDL_OBJECTTRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class ObjectTransform {
public:
    ObjectTransform(glm::vec2 position, glm::vec2 size): leftTopPosition(position), size(size){
        transformMatrix = glm::ortho(0.0f, (float) 800, (float) 600, 0.0f, -1.0f, 1.0f);
        rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1));
        objMatrix = transformMatrix * rotateMatrix;
    }

    void setSize(glm::vec2 newSize){
        size = newSize;
    }


    void setPosition(glm::vec2 position){
        leftTopPosition = position;
    }

    glm::vec2 getPosition(){
        return leftTopPosition;
    }

    void setCenterPosition(glm::vec2 center){
        centerPosition = center - size / 2.f;
    }

    glm::vec2 getCenterPosition(){
        return centerPosition;
    }

    void setRotationAngle(float_t rotationAngle){
        rotate = rotationAngle;
        glm::vec2 objectCenter = leftTopPosition + 0.5f * size;

        // Переводим центр координат объекта в начало координат
        glm::mat4 translateToOrigin = glm::translate(glm::mat4(1.0f), glm::vec3(-objectCenter, 0.0f));

        // Выполняем поворот
        glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(0, 0, 1));

        // Возвращаем центр координат объекта обратно в его исходное положение
        glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), glm::vec3(objectCenter, 0.0f));

        // Собираем все матрицы вместе
        glm::mat4 resultMatrix = transformMatrix * translateBack * rotateMatrix * translateToOrigin;


        objMatrix = resultMatrix;
    }

    virtual float_t getAngle(){
        return rotate;
    }

    glm::mat4 getTransform(){
        return objMatrix;
    }

private:
    glm::vec2 centerPosition{};
    glm::vec2 leftTopPosition{};
    glm::vec2 size{};

    float_t scale{1};
    float_t rotate{0};

    glm::mat4 transformMatrix{0};
    glm::mat4 rotateMatrix{0};
    glm::mat4 objMatrix{0};
};


#endif //INC_2DSDL_OBJECTTRANSFORM_H
