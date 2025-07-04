#ifndef INC_2DSDL_CALLBACKTIMER_H
#define INC_2DSDL_CALLBACKTIMER_H

#include <chrono>
#include <functional>
#include <vector>

class CallbackTimer {
public:
    CallbackTimer() = default;

    void addCallback(const std::function<void()>& callback, int interval_ms);

    void update();


private:
    struct Callback {
        std::function<void()> callback;
        int interval_ms;
        std::chrono::steady_clock::time_point last_time;
    };

    std::vector<Callback> callbacks;
};

#endif //INC_2DSDL_CALLBACKTIMER_H
