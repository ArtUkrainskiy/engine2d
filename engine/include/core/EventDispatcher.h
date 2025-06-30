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

    void registerListener(EventType event, const EventCallback& callback) {
        listeners[event].push_back(callback);
    }

    void dispatch(EventType event, const std::shared_ptr<Object>& trigger) {
        if (listeners.find(event) != listeners.end()) {
            for (auto& callback : listeners[event]) {
                callback(event, trigger);
            }
        }
    }

private:
    std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};


#endif //ENGINE_EVENTDISPATCHER_H
