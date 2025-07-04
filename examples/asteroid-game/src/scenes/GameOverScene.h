//
// Created by Claude Code
//

#ifndef ENGINE_GAMEOVERSCENE_H
#define ENGINE_GAMEOVERSCENE_H

#include <Engine.h>
#include "GameScene.h"
#include "MenuScene.h"

class GameOverScene : public IGameScene, public std::enable_shared_from_this<GameOverScene> {
public:
    void initialize() override {
        IGameScene::initialize(); // Create scene-scoped InputHandler
        
        auto resourceManager = ServiceProvider::get<ResourceManager>();
        
        auto mainLayer = std::make_shared<RenderLayer>();
        layers.push_back(mainLayer);

        auto windowSize = ServiceProvider::get<IWindow>()->getWindowSize();
        
        // Background
        auto background = std::make_shared<Object>(
            glm::vec2(0, 0),
            windowSize,
            resourceManager->get<Shader>("blue_paper")
        );
        mainLayer->addObject(background);

        // Game Over title
        auto gameOverLabel = std::make_shared<TextLabel>(
            glm::vec2(300, 150),  // Centered horizontally, top area
            resourceManager->get<Shader>("rectTextured"),
            "GAME OVER"
        );
        mainLayer->addObject(gameOverLabel);

        // Final Score - large and centered
        finalScoreLabel = std::make_shared<TextLabel>(
            glm::vec2(250, 250),  // Center of screen
            resourceManager->get<Shader>("rectTextured"),
            "FINAL SCORE: " + std::to_string(finalScore)
        );

        mainLayer->addObject(finalScoreLabel);

        // Retry Button
        auto retryButton = UIBuilder::createButton(
            glm::vec2(250, 350),  // Below score
            glm::vec2(120, 45),
            "RETRY",
            {0.2f, 0.8f, 0.2f, 1.0f}  // Green color
        );

        retryButton->onClick([]() {
            // Reset score and restart game
            ServiceProvider::get<ScoreManager>()->resetScore();
            
            auto sceneManager = ServiceProvider::get<SceneManager>();
            
            // Remove old scene and create new one to avoid crashes
            sceneManager->removeScene<GameScene>();
            sceneManager->createScene<GameScene>();
            sceneManager->activate<GameScene>();
        });

        mainLayer->addObject(retryButton);
        getInputHandler()->addObserver(retryButton);

        // Exit Button
        auto exitButton = UIBuilder::createButton(
            glm::vec2(430, 350),  // Next to retry button
            glm::vec2(120, 45),
            "EXIT",
            {0.8f, 0.2f, 0.2f, 1.0f}  // Red color
        );

        exitButton->onClick([]() {
            auto sceneManager = ServiceProvider::get<SceneManager>();
            sceneManager->removeScene<GameScene>();
            sceneManager->activate<MenuScene>();
        });

        mainLayer->addObject(exitButton);
        getInputHandler()->addObserver(exitButton);
    }

    void activate() override {
        finalScore = ServiceProvider::get<ScoreManager>()->getScore();
        finalScoreLabel->setText("FINAL SCORE: " + std::to_string(finalScore));
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
    int finalScore = 0;
    std::shared_ptr<TextLabel> finalScoreLabel = nullptr;
};

#endif //ENGINE_GAMEOVERSCENE_H