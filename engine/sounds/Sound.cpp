#include "Sound.h"

#include <iostream>
#include <SDL_mixer.h>

Sound::Sound(const std::string &filename) : m_filename(filename), m_chunk(nullptr), m_music(nullptr) {
    if (filename.empty()) {
        std::cerr << "Error: Empty filename provided to Sound constructor" << std::endl;
        return;
    }
    load();
}

Sound::~Sound() {
    unload();
}

void Sound::load() {
    if (m_filename.empty()) {
        std::cerr << "Error: No filename specified for sound loading" << std::endl;
        return;
    }

    // Try loading as a chunk first (for sound effects)
    m_chunk = Mix_LoadWAV(m_filename.c_str());
    if (m_chunk == nullptr) {
        std::cerr << "Warning: Failed to load sound chunk from " << m_filename
                  << " - " << Mix_GetError() << std::endl;
    }

    // Try loading as music (for background music)
    m_music = Mix_LoadMUS(m_filename.c_str());
    if (m_music == nullptr) {
        std::cerr << "Warning: Failed to load music from " << m_filename
                  << " - " << Mix_GetError() << std::endl;
    }

    if (!m_chunk && !m_music) {
        std::cerr << "Error: Failed to load sound file " << m_filename
                  << " as either chunk or music" << std::endl;
    }
}

void Sound::unload() {
    if (m_chunk != nullptr) {
        Mix_FreeChunk(m_chunk);
        m_chunk = nullptr;
    }
    if (m_music != nullptr) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}

Mix_Chunk *Sound::getChunk() const {
    return m_chunk;
}

Mix_Music *Sound::getMusic() const {
    return m_music;
}

const std::string &Sound::getFilename() const {
    return m_filename;
}