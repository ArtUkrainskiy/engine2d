#ifndef INC_2DSDL_INPUTHANDLER_H
#define INC_2DSDL_INPUTHANDLER_H

#include <memory>
#include <vector>
#include "IEventObserver.h"

class InputHandler {
public:
    void handleInput();
    
    // Handle input and return whether to propagate system events
    bool handleInputWithSystemEvents();

    void addObserver(const std::shared_ptr<IEventObserver>& observer);
    
    // Legacy support for raw pointers (deprecated)
    void addObserver(IEventObserver* observer);

    void removeObserver(const std::shared_ptr<IEventObserver>& observer);
    
    // Forward event to observers without polling SDL
    void forwardEvent(SDL_Event& event);

private:
    void notify(SDL_Event& event);

    std::vector<std::weak_ptr<IEventObserver>> observers;
};



#endif //INC_2DSDL_INPUTHANDLER_H
