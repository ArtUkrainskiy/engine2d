//
// Created by artem on 26.06.24.
//

#ifndef ENGINE_TEXTLABEL_H
#define ENGINE_TEXTLABEL_H

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <utility>
#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../graphics/TexturedObject.h"
#include "../core/ResourceManager.h"
#include "../core/ServiceProvider.h"

class TextLabel : public TexturedObject {
public:
    TextLabel(glm::vec2 position, const std::shared_ptr<Shader> &shader, const std::string &text) :
            TexturedObject(position, {}, shader, nullptr), text(text) {

        auto resourceManager = ServiceProvider::get<ResourceManager>();
        font = resourceManager->get<Font>("OpenSans-Regular");
        texture = font->renderText(text, 0, 0, {255, 255, 255, 0});
        setSize(texture->getSize());
        setTexture(texture);

    }


    void setText(const std::string &newText) {
        text = newText;
        texture = font->renderText(newText, 0, 0, {255, 255, 255, 0});
        setSize(texture->getSize());
        setTexture(texture);
    }


private:
    std::string text;
    std::shared_ptr<Font> font;
    std::shared_ptr<Texture> texture;
};


#endif //ENGINE_TEXTLABEL_H
