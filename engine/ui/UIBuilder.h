#ifndef ENGINE_UIBUILDER_H
#define ENGINE_UIBUILDER_H

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "Button.h"

class UIBuilder {
public:
    UIBuilder() = default;

    static std::shared_ptr<Button> createButton(glm::vec2 position, glm::vec2 size, const std::string &text, glm::vec4 textColor);

private:


};


#endif //ENGINE_UIBUILDER_H
