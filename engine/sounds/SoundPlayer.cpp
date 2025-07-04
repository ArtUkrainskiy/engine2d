#include "sounds/SoundPlayer.h"
#include <iostream>
#include <SDL.h>


SoundPlayer::SoundPlayer() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error: Failed to initialize SDL audio - " << SDL_GetError() << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "Error: Failed to open audio device - " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    std::cout << "SoundPlayer initialized successfully" << std::endl;
}

SoundPlayer::~SoundPlayer() {
    stop(); // Stop all playing sounds
    Mix_CloseAudio();
    SDL_Quit();
}

void SoundPlayer::playOnce(const Sound &sound) {
    if (!sound.getChunk()) {
        std::cerr << "Error: Cannot play sound - no chunk available for " 
                  << sound.getFilename() << std::endl;
        return;
    }

    if (m_playingSounds.find(sound.getFilename()) == m_playingSounds.end()) {
        int channel = Mix_PlayChannel(-1, sound.getChunk(), 0);
        if (channel == -1) {
            std::cerr << "Error: Failed to play sound " << sound.getFilename() 
                      << " - " << Mix_GetError() << std::endl;
        } else {
            m_playingSounds.insert(sound.getFilename());
        }
    }
}

void SoundPlayer::playLoop(const Sound &sound) {
    if (!sound.getMusic()) {
        std::cerr << "Error: Cannot play music - no music available for " 
                  << sound.getFilename() << std::endl;
        return;
    }

    if (Mix_PlayMusic(sound.getMusic(), -1) == -1) {
        std::cerr << "Error: Failed to play music " << sound.getFilename() 
                  << " - " << Mix_GetError() << std::endl;
    }
}

void SoundPlayer::stop() {
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    m_playingSounds.clear();
}