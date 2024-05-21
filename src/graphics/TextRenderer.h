//
// Created by artem on 29.04.24.
//

#ifndef INC_2DSDL_TEXTRENDERER_H
#define INC_2DSDL_TEXTRENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <memory>
#include "Texture.h"


class TextRenderer {
public:
    TextRenderer(const std::string &fontFile, int fontSize) {
        if (TTF_Init() == -1) {
            // Handle error
        }

        font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (!font) {
            // Handle error
        }

    }

    ~TextRenderer() {
        TTF_CloseFont(font);
        TTF_Quit();
    }

    std::shared_ptr<Texture> renderText(const std::string &text, int x, int y, SDL_Color color) {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        auto texture =  std::make_shared<Texture>(surface);
        SDL_FreeSurface(surface);

        return texture;
    }

private:
    TTF_Font *font;
};


#endif //INC_2DSDL_TEXTRENDERER_H
