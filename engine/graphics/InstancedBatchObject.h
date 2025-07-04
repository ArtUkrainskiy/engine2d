#ifndef INC_2DSDL_INSTANCEDBATCHOBJECT_H
#define INC_2DSDL_INSTANCEDBATCHOBJECT_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "Object.h"
#include "Shader.h"
#include "VertexArrayObject.h"

struct InstanceData2D {
    glm::vec2 position;    // 2 float - позиция центра
    glm::vec2 size;        // 2 float - размер
    float rotation;        // 1 float - угол в радианах
    glm::vec4 color;       // 4 float - цвет
    // Итого: 9 float вместо 20 (на 55% меньше!)
};

class InstancedBatchObject : public Object {
public:
    explicit InstancedBatchObject(const std::shared_ptr<Shader>& shader);

    void addObject(const std::shared_ptr<Object>& object);

    void removeObject(const std::shared_ptr<Object>& object);

    void clear();

    void buildInstances();

    void draw() override;

    size_t getObjectCount() const;

    bool isEmpty() const;

    void makeDirty();

private:
    void setupUnitQuad();

    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<VertexArrayObject> vao;
    std::shared_ptr<Shader> shader;
    std::vector<InstanceData2D> instanceData;
    bool instancesDirty;
    bool quadSetup;
    bool vaoInitialized;
};

#endif //INC_2DSDL_INSTANCEDBATCHOBJECT_H