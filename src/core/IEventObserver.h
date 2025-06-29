//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_EVENTOBSERVER_H
#define INC_2DSDL_EVENTOBSERVER_H


#include <SDL_events.h>

class IEventObserver {
public:
    virtual void onNotify(SDL_Event& event) = 0;
};


#endif //INC_2DSDL_EVENTOBSERVER_H
