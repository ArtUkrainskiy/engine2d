//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_INPUTHANDLER_H
#define INC_2DSDL_INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "IEventObserver.h"

class InputHandler {
public:
    void handleInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            notify(event);
        }
    }
    
    // Handle input and return whether to propagate system events
    bool handleInputWithSystemEvents() {
        SDL_Event event;
        bool hasSystemEvents = false;
        
        while (SDL_PollEvent(&event)) {
            // Check for system events first
            if (event.type == SDL_QUIT) {
                hasSystemEvents = true;
            }
            
            notify(event);
        }
        
        return hasSystemEvents;
    }

    void addObserver(const std::shared_ptr<IEventObserver>& observer) {
        observers.push_back(observer);
    }
    
    // Legacy support for raw pointers (deprecated)
    void addObserver(IEventObserver* observer) {
        // For legacy code that doesn't use shared_ptr
        // Note: This is unsafe but provides backwards compatibility
        if (observer) {
            try {
                if (auto sharedObserver = observer->shared_from_this()) {
                    observers.push_back(sharedObserver);
                }
            } catch (const std::bad_weak_ptr&) {
                // Object is not managed by shared_ptr - skip for safety
                std::cerr << "Warning: Observer not managed by shared_ptr, skipping" << std::endl;
            }
        }
    }

    void removeObserver(const std::shared_ptr<IEventObserver>& observer) {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [observer](const std::weak_ptr<IEventObserver>& weak) {
                    return weak.lock() == observer;
                }),
            observers.end()
        );
    }
    
    // Forward event to observers without polling SDL
    void forwardEvent(SDL_Event& event) {
        // Clean up expired observers
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](const std::weak_ptr<IEventObserver>& weak) {
                    return weak.expired();
                }),
            observers.end()
        );
        
        // Notify all valid observers
        for (auto& weak : observers) {
            if (auto observer = weak.lock()) {
                observer->onNotify(event);
            }
        }
    }

private:
    void notify(SDL_Event& event) {
        // Clean up expired observers and notify valid ones
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](const std::weak_ptr<IEventObserver>& weak) {
                    return weak.expired();
                }),
            observers.end()
        );
        
        // Notify all valid observers
        for (auto& weak : observers) {
            if (auto observer = weak.lock()) {
                observer->onNotify(event);
            }
        }
    }

    std::vector<std::weak_ptr<IEventObserver>> observers;
};



#endif //INC_2DSDL_INPUTHANDLER_H
