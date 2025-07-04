#ifndef INC_2DSDL_TEXTRENDERER_H
#define INC_2DSDL_TEXTRENDERER_H

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"


class Font : public IResource {
public:
    Font(const std::string& fontFile, const int fontSize) {
        if (TTF_Init() == -1) {
            // Handle error
        }

        font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (!font) {
            // Handle error
        }
    }

    ~Font() {
        TTF_CloseFont(font);
        TTF_Quit();
    }

    [[nodiscard]] std::shared_ptr<Texture> renderText(const std::string& text, int x, int y,
                                                      const SDL_Color color) const {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        auto texture = std::make_shared<Texture>(surface);
        SDL_FreeSurface(surface);

        return texture;
    }

private:
    TTF_Font* font;
};


#endif //INC_2DSDL_TEXTRENDERER_H
