#include "core/InputHandler.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>


void InputHandler::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        notify(event);
    }
}

bool InputHandler::handleInputWithSystemEvents() {
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

void InputHandler::addObserver(const std::shared_ptr<IEventObserver>& observer) {
    if (!observer) {
        std::cerr << "Warning: Attempting to add null observer" << std::endl;
        return;
    }
    observers.push_back(observer);
}

void InputHandler::addObserver(IEventObserver* observer) {
    // For legacy code that doesn't use shared_ptr
    // Note: This is unsafe but provides backwards compatibility
    if (!observer) {
        std::cerr << "Warning: Attempting to add null observer" << std::endl;
        return;
    }
    
    try {
        if (auto sharedObserver = observer->shared_from_this()) {
            observers.push_back(sharedObserver);
        }
    } catch (const std::bad_weak_ptr&) {
        // Object is not managed by shared_ptr - skip for safety
        std::cerr << "Warning: Observer not managed by shared_ptr, skipping" << std::endl;
    }
}

void InputHandler::removeObserver(const std::shared_ptr<IEventObserver>& observer) {
    if (!observer) {
        std::cerr << "Warning: Attempting to remove null observer" << std::endl;
        return;
    }
    
    observers.erase(
        std::remove_if(observers.begin(), observers.end(),
            [observer](const std::weak_ptr<IEventObserver>& weak) {
                return weak.lock() == observer;
            }),
        observers.end()
    );
}

void InputHandler::forwardEvent(SDL_Event& event) {
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

void InputHandler::notify(SDL_Event& event) {
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