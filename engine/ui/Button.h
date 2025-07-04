#ifndef INC_2DSDL_BUTTON_H
#define INC_2DSDL_BUTTON_H

#include <functional>
#include "../core/IEventObserver.h"
#include "../graphics/WireObject.h"

class Button final : public WireObject, public IEventObserver {
public:
    Button(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader, glm::vec4 color);


    void onNotify(SDL_Event &event) override;

    void onClick(const std::function<void()>& callback);


    void clicked();

private:
    std::function<void()> clickCallback;

    bool isInside(const glm::vec2 &point, const glm::vec2 &pos, const glm::vec2 &size);
};


#endif //INC_2DSDL_BUTTON_H
