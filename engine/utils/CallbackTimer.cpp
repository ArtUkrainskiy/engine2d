#include "utils/CallbackTimer.h"
#include <iostream>

void CallbackTimer::addCallback(const std::function<void()>& callback, const int interval_ms) {
    if (!callback) {
        std::cerr << "Error: Attempting to add null callback to timer" << std::endl;
        return;
    }
    
    if (interval_ms <= 0) {
        std::cerr << "Error: Invalid interval " << interval_ms << "ms for callback timer" << std::endl;
        return;
    }
    
    callbacks.push_back({callback, interval_ms, std::chrono::steady_clock::now()});
}

void CallbackTimer::update() {
    auto current_time = std::chrono::steady_clock::now();
    
    for (auto &cb: callbacks) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - cb.last_time).count();
        
        if (elapsed >= cb.interval_ms) {
            try {
                cb.callback();
                cb.last_time = current_time;
            } catch (const std::exception& e) {
                std::cerr << "Error in callback timer: " << e.what() << std::endl;
            }
        }
    }
}