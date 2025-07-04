#ifndef ENGINE_EVENTDISPATCHER_H
#define ENGINE_EVENTDISPATCHER_H


#include <functional>
#include <unordered_map>
#include <vector>

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

    ListenerId registerListener(EventType event, const EventCallback& callback);

    void unregisterListener(EventType event, ListenerId listenerId);

    void dispatch(EventType event, const std::shared_ptr<Object>& trigger);

private:
    std::unordered_map<EventType, std::vector<std::pair<ListenerId, EventCallback>>> listeners;
    ListenerId nextListenerId = 1;
};


#endif //ENGINE_EVENTDISPATCHER_H
