#ifndef ENGINE_TEXTLABEL_H
#define ENGINE_TEXTLABEL_H

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include "../core/ResourceManager.h"
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/TexturedObject.h"

class TextLabel : public TexturedObject {
public:
    TextLabel(glm::vec2 position, const std::shared_ptr<Shader> &shader, const std::string &text);


    void setText(const std::string &newText);


private:
    std::string text;
    std::shared_ptr<Font> font;
    std::shared_ptr<Texture> texture;
};


#endif //ENGINE_TEXTLABEL_H
