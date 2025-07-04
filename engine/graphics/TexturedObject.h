#ifndef INC_2DSDL_TEXTUREDOBJECT_H
#define INC_2DSDL_TEXTUREDOBJECT_H

#include <memory>
#include <glm/glm.hpp>

#include "Object.h"
#include "Shader.h"
#include "Texture.h"

class TexturedObject : public Object {
public:
    TexturedObject(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
                   const std::shared_ptr<Texture> &texture);

    void setTexture(std::shared_ptr<Texture> texture);

    void setMaterial(std::shared_ptr<Shader> shader);

    void draw() override;

protected:
    std::shared_ptr<Texture> texture;

private:
    void setupTextureCoordinates();

};


#endif //INC_2DSDL_TEXTUREDOBJECT_H
