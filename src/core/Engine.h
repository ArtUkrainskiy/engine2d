//
// Created by artem on 12.06.24.
//

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H


#include "ServiceInitializer.h"
#include "../utils/FPSCounter.h"

class Engine: public ServiceInitializer {
public:
    Engine(){
        fpsCounter = new FPSCounter();
    }


    bool update(){
        const auto timeDelta = fpsCounter->update();
        renderer->draw();
        sceneManager->getActiveScene()->update(timeDelta);
        sceneManager->getActiveScene()->render(timeDelta);
        return window && window->update();
    }


private:
    FPSCounter *fpsCounter;
};


#endif //ENGINE_ENGINE_H
