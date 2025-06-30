//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_EVENTOBSERVER_H
#define INC_2DSDL_EVENTOBSERVER_H


#include <SDL_events.h>
#include <memory>

class IEventObserver : public std::enable_shared_from_this<IEventObserver> {
public:
    virtual ~IEventObserver() = default;
    virtual void onNotify(SDL_Event& event) = 0;
};


#endif //INC_2DSDL_EVENTOBSERVER_H
