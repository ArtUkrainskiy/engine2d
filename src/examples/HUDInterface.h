//
// Created by artem on 27.06.24.
//

#ifndef ENGINE_HUDINTERFACE_H
#define ENGINE_HUDINTERFACE_H


#include <memory>
#include "../UI/TextLabel.h"
#include "../graphics/RenderLayer.h"
#include "../game/Player.h"

class HUDInterface {
public:
    HUDInterface(const std::shared_ptr<RenderLayer> &renderLayer, const std::shared_ptr<Player> &player) :
            renderLayer(renderLayer), player(player), paused(false) {
        auto resourceManager = ServiceProvider::get<ResourceManager>();

        scoreManager = ServiceProvider::get<ScoreManager>();

        scoreLabel = std::make_shared<TextLabel>(
                glm::vec2(10, 10),  // Верхний левый угол для счета
                resourceManager->get<Shader>("rectTextured"),
                "SCORE: " + std::to_string(scoreManager->getScore())
        );

        hpLabel = std::make_shared<TextLabel>(
                glm::vec2(10, 570),  // Нижний левый угол для здоровья
                resourceManager->get<Shader>("rectTextured"),
                "HEALTH: " + std::to_string(100) + "%"
        );

        pauseLabel = std::make_shared<TextLabel>(
                glm::vec2(350, 250),  // Центр экрана для паузы: (800/2 - 50) = 350, (600/2 - 50) = 250
                resourceManager->get<Shader>("rectTextured"),
                "PAUSE"
        );

        renderLayer->addObject(scoreLabel);
        renderLayer->addObject(hpLabel);


    }

    void pause(){
        paused = !paused;
        if(paused){
            renderLayer->addObject(pauseLabel);
        }else{
            renderLayer->removeObject(pauseLabel);
        }
    }

    void update(float deltaTime) {
        hpLabel->setText("HEALTH: " + std::to_string(player->getHealth()) + "%");
        scoreLabel->setText("SCORE: " + std::to_string(scoreManager->getScore()));
    }


private:
    std::shared_ptr<RenderLayer> renderLayer;
    std::shared_ptr<Player> player;
    std::shared_ptr<TextLabel> hpLabel;
    std::shared_ptr<TextLabel> scoreLabel;
    std::shared_ptr<TextLabel> pauseLabel;
    ScoreManager *scoreManager;

    bool paused;
};


#endif //ENGINE_HUDINTERFACE_H
