#include "core/EventDispatcher.h"
#include <iostream>

EventDispatcher::ListenerId EventDispatcher::registerListener(EventType event, const EventCallback& callback) {
    if (!callback) {
        std::cerr << "Warning: Attempting to register null callback" << std::endl;
        return 0;
    }
    
    ListenerId id = nextListenerId++;
    listeners[event].emplace_back(id, callback);
    return id;
}

void EventDispatcher::unregisterListener(EventType event, ListenerId listenerId) {
    if (listenerId == 0) {
        std::cerr << "Warning: Invalid listener ID" << std::endl;
        return;
    }
    
    if (listeners.find(event) != listeners.end()) {
        auto& eventListeners = listeners[event];
        eventListeners.erase(
            std::remove_if(eventListeners.begin(), eventListeners.end(),
                [listenerId](const auto& pair) { return pair.first == listenerId; }),
            eventListeners.end()
        );
    }
}

void EventDispatcher::dispatch(EventType event, const std::shared_ptr<Object>& trigger) {
    if (listeners.find(event) != listeners.end()) {
        for (auto& [id, callback] : listeners[event]) {
            try {
                callback(event, trigger);
            } catch (const std::exception& e) {
                std::cerr << "Error in event callback: " << e.what() << std::endl;
            }
        }
    }
}