#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>
#include <graphics/IResource.h>

class Sound : public IResource {
public:
    Sound(const std::string &filename);

    ~Sound();

    void load();

    void unload();

    Mix_Chunk *getChunk() const;

    Mix_Music *getMusic() const;

    const std::string &getFilename() const;

private:
    std::string m_filename;
    Mix_Chunk *m_chunk;
    Mix_Music *m_music;
};



#endif //SOUND_H
