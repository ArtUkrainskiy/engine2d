//
// Created by artem.ukrainskiy on 27.06.25.
//

#ifndef INC_2DSDL_BATCHEDOBJECT_H
#define INC_2DSDL_BATCHEDOBJECT_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../graphics/VertexArrayObject.h"
#include "../graphics/Shader.h"
#include "BatchInstance.h"

struct InstanceData {
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
    bool active = true;
};

class BatchedObject {
public:
    explicit BatchedObject(const std::shared_ptr<Shader>& shader);
    ~BatchedObject();

    std::shared_ptr<BatchInstance> addInstance(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void removeInstance(size_t index);
    void removeInstance(const std::shared_ptr<BatchInstance>& instance);

    void updateInstance(size_t index, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    
    void draw();
    void setProjectionMatrix(const glm::mat4& projection);

    size_t getInstanceCount() const { return instances.size(); }
    size_t getActiveInstanceCount() const;
    
    std::shared_ptr<Shader> getShader() const { return shader; }

private:
    void setupBuffers();
    void updateInstanceBuffer();
    void rebuildInstanceBuffer();

    std::shared_ptr<Shader> shader;
    std::shared_ptr<VertexArrayObject> vao;
    
    std::vector<InstanceData> instances;
    std::vector<std::weak_ptr<BatchInstance>> instanceRefs;
    std::vector<size_t> freeIndices;
    
    bool bufferDirty = true;
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

    static constexpr size_t VERTICES_PER_QUAD = 6;
    static const float QUAD_VERTICES[VERTICES_PER_QUAD * 2];
};

#endif //INC_2DSDL_BATCHEDOBJECT_H