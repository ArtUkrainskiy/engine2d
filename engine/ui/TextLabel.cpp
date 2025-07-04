#include "ui/TextLabel.h"
#include <iostream>
#include <core/ServiceProvider.h>

TextLabel::TextLabel(glm::vec2 position, const std::shared_ptr<Shader> &shader, const std::string &text) :
        TexturedObject(position, {}, shader, nullptr), text(text) {

    auto resourceManager = ServiceProvider::get<ResourceManager>();
    if (!resourceManager) {
        std::cerr << "Error: ResourceManager not available for TextLabel" << std::endl;
        return;
    }

    font = resourceManager->get<Font>("OpenSans-Regular");
    if (!font) {
        std::cerr << "Error: Font 'OpenSans-Regular' not found for TextLabel" << std::endl;
        return;
    }

    texture = font->renderText(text, 0, 0, {255, 255, 255, 0});
    if (!texture) {
        std::cerr << "Error: Failed to render text '" << text << "' for TextLabel" << std::endl;
        return;
    }

    setSize(texture->getSize());
    setTexture(texture);
}

void TextLabel::setText(const std::string &newText) {
    if (text == newText) {
        return; // No change needed
    }

    text = newText;
    
    if (!font) {
        std::cerr << "Error: No font available for setText" << std::endl;
        return;
    }

    texture = font->renderText(newText, 0, 0, {255, 255, 255, 0});
    if (!texture) {
        std::cerr << "Error: Failed to render new text '" << newText << "'" << std::endl;
        return;
    }

    setSize(texture->getSize());
    setTexture(texture);
}