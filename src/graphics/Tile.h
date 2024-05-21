//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_TILE_H
#define INC_2DSDL_TILE_H


#include "Texture.h"

class Tile {

public:
    void setTexture(Texture *pTexture);

    void move(int i, int i1);
};


#endif //INC_2DSDL_TILE_H
