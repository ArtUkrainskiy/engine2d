//
// Created by artem on 28.04.24.
//

#ifndef INC_2DSDL_SOUNDPLAYER_H
#define INC_2DSDL_SOUNDPLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_set>

class Sound {
public:
    Sound(const std::string &filename) : m_filename(filename), m_chunk(nullptr), m_music(nullptr) {
        load();
    }

    ~Sound() {
        unload();
    }

    void load() {
        m_chunk = Mix_LoadWAV(m_filename.c_str());
        if (m_chunk == nullptr) {
            // handle loading error
        }
        m_music = Mix_LoadMUS(m_filename.c_str());
        if (m_music == nullptr) {
            // handle loading error
        }
    }

    void unload() {
        if (m_chunk != nullptr) {
            Mix_FreeChunk(m_chunk);
            m_chunk = nullptr;
        }
        if (m_music != nullptr) {
            Mix_FreeMusic(m_music);
            m_music = nullptr;
        }
    }

    Mix_Chunk *getChunk() const {
        return m_chunk;
    }

    Mix_Music *getMusic() const {
        return m_music;
    }

    const std::string &getFilename() const {
        return m_filename;
    }

private:
    std::string m_filename;
    Mix_Chunk *m_chunk;
    Mix_Music *m_music;
};

class SoundPlayer {
public:
    SoundPlayer() {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            // handle initialization error
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
            // handle audio initialization error
        }
    }

    ~SoundPlayer() {
        Mix_CloseAudio();
        SDL_Quit();
    }

    void playOnce(const Sound &sound) {
        if (m_playingSounds.find(sound.getFilename()) == m_playingSounds.end()) {
            Mix_PlayChannel(-1, sound.getChunk(), 0);
            m_playingSounds.insert(sound.getFilename());
        }
    }

    void playLoop(const Sound &sound) {
        Mix_PlayMusic(sound.getMusic(), -1);
    }

    void stop() {
        Mix_HaltChannel(-1);
        m_playingSounds.clear();
    }

private:
    std::unordered_set<std::string> m_playingSounds;
};


#endif //INC_2DSDL_SOUNDPLAYER_H
