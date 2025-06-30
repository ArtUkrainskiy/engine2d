//
// Created by artem on 12.06.24.
//

#ifndef ENGINE_UIBUILDER_H
#define ENGINE_UIBUILDER_H


#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "Button.h"
#include "../core/ResourceManager.h"
#include "../core/ServiceProvider.h"
#include "../graphics/TexturedObject.h"

class UIBuilder {
public:
    UIBuilder() = default;

    static std::shared_ptr<Button> createButton(glm::vec2 position, glm::vec2 size, const std::string &text, glm::vec4 textColor) {
        auto resourceManager = ServiceProvider::get<ResourceManager>();
        auto wireShader = resourceManager->get<Shader>("rect");
        auto texturedShader = resourceManager->get<Shader>("rectTextured");
        auto font = resourceManager->get<Font>("OpenSans-Regular");
        auto button = std::make_shared<Button>(position, size, wireShader, textColor);

        auto retryTexture = font->renderText(text, 0, 0, {255, 0, 0, 0});
        auto textureObject = std::make_shared<TexturedObject>(
                glm::vec2(0, 0),  // Позиция будет установлена в addChild
                retryTexture->getSize(),
                texturedShader,
                retryTexture
        );

        button->addChild(textureObject);

        return button;


    }

private:


};


#endif //ENGINE_UIBUILDER_H
