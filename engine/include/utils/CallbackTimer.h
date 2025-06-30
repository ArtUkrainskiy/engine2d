//
// Created by artem on 16.05.24.
//

#ifndef INC_2DSDL_CALLBACKTIMER_H
#define INC_2DSDL_CALLBACKTIMER_H

#include <iostream>
#include <functional>
#include <chrono>
#include <vector>
#include <algorithm>

class CallbackTimer {
public:
    CallbackTimer() = default;

    void addCallback(std::function<void()> callback, int interval_ms) {
        callbacks.push_back({callback, interval_ms, std::chrono::steady_clock::now()});
    }

    void update() {
        auto current_time = std::chrono::steady_clock::now();
        for (auto &cb: callbacks) {
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - cb.last_time).count();
            if (elapsed >= cb.interval_ms) {
                cb.callback();
                cb.last_time = current_time;
            }
        }
    }


private:
    struct Callback {
        std::function<void()> callback;
        int interval_ms;
        std::chrono::steady_clock::time_point last_time;
    };

    std::vector<Callback> callbacks;
};

#endif //INC_2DSDL_CALLBACKTIMER_H
