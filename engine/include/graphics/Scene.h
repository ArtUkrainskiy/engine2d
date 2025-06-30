//
// Created by artem on 07.04.24.
//

#ifndef INC_2DSDL_SCENE_H
#define INC_2DSDL_SCENE_H


#include <vector>
#include <memory>


#include "RenderLayer.h"
#include "Tile.h"
#include "../core/IGameScene.h"

class Scene : public IGameScene {
public:
    void initialize() override {

    }

    void activate() override {

    }

    void update(float timeDelta) override {

    }

    void deactivate() override {

    }

    void destroy() override {

    }

    void render(float timeDelta) override{
        for (const auto &item: layers){
            item->draw();
        }
    }

private:

};


#endif //INC_2DSDL_SCENE_H
