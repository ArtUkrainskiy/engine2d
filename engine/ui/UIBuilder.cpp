#include "ui/UIBuilder.h"

#include <iostream>
#include <core/ResourceManager.h>
#include <core/ServiceProvider.h>
#include <graphics/TexturedObject.h>

std::shared_ptr<Button> UIBuilder::createButton(glm::vec2 position, glm::vec2 size, const std::string &text, glm::vec4 textColor) {
    auto resourceManager = ServiceProvider::get<ResourceManager>();
    if (!resourceManager) {
        std::cerr << "Error: ResourceManager not available for UIBuilder" << std::endl;
        return nullptr;
    }

    auto wireShader = resourceManager->get<Shader>("rect");
    if (!wireShader) {
        std::cerr << "Error: Wire shader 'rect' not found for button creation" << std::endl;
        return nullptr;
    }

    auto texturedShader = resourceManager->get<Shader>("rectTextured");
    if (!texturedShader) {
        std::cerr << "Error: Textured shader 'rectTextured' not found for button creation" << std::endl;
        return nullptr;
    }

    auto font = resourceManager->get<Font>("OpenSans-Regular");
    if (!font) {
        std::cerr << "Error: Font 'OpenSans-Regular' not found for button creation" << std::endl;
        return nullptr;
    }

    auto button = std::make_shared<Button>(position, size, wireShader, textColor);
    if (!button) {
        std::cerr << "Error: Failed to create button" << std::endl;
        return nullptr;
    }

    auto retryTexture = font->renderText(text, 0, 0, {255, 0, 0, 0});
    if (!retryTexture) {
        std::cerr << "Error: Failed to render button text '" << text << "'" << std::endl;
        return button; // Return button without text
    }

    auto textureObject = std::make_shared<TexturedObject>(
            glm::vec2(0, 0),  // Позиция будет установлена в addChild
            retryTexture->getSize(),
            texturedShader,
            retryTexture
    );

    if (textureObject) {
        button->addChild(textureObject);
    } else {
        std::cerr << "Error: Failed to create textured object for button text" << std::endl;
    }

    return button;
}
