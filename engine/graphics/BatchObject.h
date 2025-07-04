#ifndef INC_2DSDL_BATCHOBJECT_H
#define INC_2DSDL_BATCHOBJECT_H

#include <memory>
#include <vector>


#include "Object.h"
#include "Shader.h"
#include "VertexArrayObject.h"


class BatchObject final : public Object {
public:
    explicit BatchObject(const std::shared_ptr<Shader>& shader);

    void addObject(const std::shared_ptr<Object>& object);

    void removeObject(const std::shared_ptr<Object>& object);

    void clear();

    void buildBatch();

    void draw() override;

    size_t getObjectCount() const;

    bool isEmpty() const;

    void makeDirty();

private:
    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<VertexArrayObject> vao;
    std::shared_ptr<Shader> shader;
    std::vector<float> cachedBatchVertices;
    bool batchDirty;
    bool geometryInitialized = false;
};

#endif //INC_2DSDL_BATCHOBJECT_H
