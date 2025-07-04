#ifndef INC_2DSDL_ANIMATIONCONTROLLER_H
#define INC_2DSDL_ANIMATIONCONTROLLER_H


#include <string>
#include <memory>
#include <map>
#include <utility>
#include "Animation.h"

class AnimationController {
public:

    void setIdleAnimation(const std::string &name) {
        idle = name;
    }

    void addAnimation(const std::string &name, std::shared_ptr<Animation> animation) {
        animations[name] = std::move(animation);
    }

    void setCurrent(const std::string &name) {
        if (!once) {
            current = name;
        }
    }

    std::shared_ptr<Animation> getCurrent() {
        return animations[current];
    }


    void playOnce(std::string name) {
        current = name;
        once = true;
    }

    void play() {
        bool finish = animations[current]->play();
        if (once and finish) {
            current = idle;
            once = false;
        }
    }

private:

    std::map<std::string, std::shared_ptr<Animation>> animations;

    bool once = false;

    std::string current;
    std::string idle;

};


#endif //INC_2DSDL_ANIMATIONCONTROLLER_H
