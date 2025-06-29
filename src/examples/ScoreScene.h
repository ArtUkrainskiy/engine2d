//
// Created by artem on 17.06.24.
//

#ifndef ENGINE_SCORESCENE_H
#define ENGINE_SCORESCENE_H

#include "../core/IGameScene.h"

class ScoreScene : public IGameScene, public std::enable_shared_from_this<ScoreScene> {
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

    void render(float timeDelta) override {
        for (const auto &item: layers) {
            item->draw();
        }
    }

};

#endif //ENGINE_SCORESCENE_H
