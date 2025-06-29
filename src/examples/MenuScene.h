//
// Created by artem on 10.06.24.
//

#ifndef ENGINE_MENUSCENE_H
#define ENGINE_MENUSCENE_H

#include <memory>
#include "../core/Engine.h"
#include "../core/IGameScene.h"
#include "../game/AsteroidManager.h"
#include "../game/AsteroidFactory.h"
#include "../core/ResourceManager.h"
#include "../UI/Button.h"
#include "../graphics/Font.h"
#include "../core/IRenderer.h"
#include "../core/InputHandler.h"
#include "../UI/UIBuilder.h"
#include "GameScene.h"

class MenuScene : public IGameScene, public std::enable_shared_from_this<MenuScene> {
public:
    void initialize() override {
        auto resourceManager = ServiceProvider::get<ResourceManager>();

        inputHandler = ServiceProvider::get<IWindow>()->getInputHandler();
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

        playButton->onClick([playButton]() {
            ServiceProvider::get<SceneManager>()->activate<GameScene>();
        });

        mainLayer->addObject(playButton);


        inputHandler->addObserver(playButton.get());
    }

    void activate() override {
        ServiceProvider::get<IRenderer>()->setActiveScene(shared_from_this());
    }

    void update(float timeDelta) override {
        inputHandler->handleInput();
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

public:
    InputHandler *inputHandler;

};


#endif //ENGINE_MENUSCENE_H
