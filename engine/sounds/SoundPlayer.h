//
// Created by artem on 28.04.24.
//

#ifndef INC_2DSDL_SOUNDPLAYER_H
#define INC_2DSDL_SOUNDPLAYER_H

#include <string>
#include <unordered_set>

#include "Sound.h"

class SoundPlayer {
public:
    SoundPlayer();

    ~SoundPlayer();

    void playOnce(const Sound &sound);

    void playLoop(const Sound &sound);

    void stop();

private:
    std::unordered_set<std::string> m_playingSounds;
};


#endif //INC_2DSDL_SOUNDPLAYER_H
