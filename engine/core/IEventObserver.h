#ifndef INC_2DSDL_EVENTOBSERVER_H
#define INC_2DSDL_EVENTOBSERVER_H


#include <memory>
#include <SDL_events.h>

class IEventObserver : public std::enable_shared_from_this<IEventObserver> {
public:
    virtual ~IEventObserver() = default;
    virtual void onNotify(SDL_Event& event) = 0;
};


#endif //INC_2DSDL_EVENTOBSERVER_H
