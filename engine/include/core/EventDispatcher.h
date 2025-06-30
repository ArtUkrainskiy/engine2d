//
// Created by artem on 31.05.24.
//

#ifndef ENGINE_EVENTDISPATCHER_H
#define ENGINE_EVENTDISPATCHER_H


#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "../graphics/Object.h"

class EventDispatcher {
public:
    enum EventType{
        EVENT_PLAY_BUTTON_PRESSED,
        EVENT_ASTEROID_DESTROYED,
        EVENT_ENEMY_DESTROYED,
        EVENT_SCORE_REACHED,
    };

    using EventCallback = std::function<void(EventType event, std::shared_ptr<Object> trigger)>;
    using ListenerId = size_t;

    ListenerId registerListener(EventType event, const EventCallback& callback) {
        ListenerId id = nextListenerId++;
        listeners[event].emplace_back(id, callback);
        return id;
    }

    void unregisterListener(EventType event, ListenerId listenerId) {
        if (listeners.find(event) != listeners.end()) {
            auto& eventListeners = listeners[event];
            eventListeners.erase(
                std::remove_if(eventListeners.begin(), eventListeners.end(),
                    [listenerId](const auto& pair) { return pair.first == listenerId; }),
                eventListeners.end()
            );
        }
    }

    void dispatch(EventType event, const std::shared_ptr<Object>& trigger) {
        if (listeners.find(event) != listeners.end()) {
            for (auto& [id, callback] : listeners[event]) {
                callback(event, trigger);
            }
        }
    }

private:
    std::unordered_map<EventType, std::vector<std::pair<ListenerId, EventCallback>>> listeners;
    ListenerId nextListenerId = 1;
};


#endif //ENGINE_EVENTDISPATCHER_H
