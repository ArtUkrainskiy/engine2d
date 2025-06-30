//
// Created by artem on 10.06.24.
//

#ifndef ENGINE_MENUSCENE_H
#define ENGINE_MENUSCENE_H

#include <memory>
#include "../game/AsteroidFactory.h"
#include "GameScene.h"

class MenuScene : public IGameScene, public std::enable_shared_from_this<MenuScene> {
public:
    void initialize() override {
        IGameScene::initialize(); // Create scene-scoped InputHandler
        
        auto resourceManager = ServiceProvider::get<ResourceManager>();

        auto mainLayer = std::make_shared<RenderLayer>();
        layers.push_back(mainLayer);

        auto windowSize = ServiceProvider::get<IWindow>()->getWindowSize();
        auto background = std::make_shared<TexturedObject>(
                glm::vec2(0, 0),
                windowSize,
                resourceManager->get<Shader>("rectTextured"),
                resourceManager->get<Texture>("background")
        );

        mainLayer->addObject(background);

        auto playButton = UIBuilder::createButton(
                glm::vec2(310, 275),  // Центрируем кнопку: (800-180)/2 = 310, (600-45)/2 = 275
                glm::vec2(180, 45),
                "Play",
                {1, 1, 1, 1}
        );

        playButton->onClick([]() {
            ServiceProvider::get<SceneManager>()->activate<GameScene>();
        });

        mainLayer->addObject(playButton);

        getInputHandler()->addObserver(playButton);
    }

    void activate() override {
        ServiceProvider::get<IRenderer>()->setActiveScene(shared_from_this());
    }

    void update(float timeDelta) override {
        // Input handled by Window - no need to call handleInput() here
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

private:

};


#endif //ENGINE_MENUSCENE_H
