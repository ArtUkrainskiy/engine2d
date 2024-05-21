//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_SCENE_H
#define INC_2DSDL_SCENE_H


#include <vector>
#include <memory>


#include "RenderLayer.h"
#include "Tile.h"

class Scene {

public:
    void addRenderLayer(const std::shared_ptr<RenderLayer>& layer){
        layers.push_back(layer);
    }

    void draw(){
        for (const auto &item: layers){
            item->draw();
        }
    }

private:

    std::vector<std::shared_ptr<RenderLayer>> layers;
};


#endif //INC_2DSDL_SCENE_H
