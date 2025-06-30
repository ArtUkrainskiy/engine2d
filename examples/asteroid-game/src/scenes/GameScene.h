//
// Created by artem on 17.06.24.
//

#ifndef ENGINE_GAMESCENE_H
#define ENGINE_GAMESCENE_H


#include <Engine.h>
#include "../game/EffectFactory.h"
#include "../game/EffectManager.h"
#include "../game/AsteroidManager.h"
#include "../game/AsteroidFactory.h"
#include "../game/Player.h"
#include "../game/ProjectilePool.h"
#include "../game/PowerupManager.h"
#include "../game/PowerupFactory.h"
#include "../game/UpgradeManager.h"
#include "../game/HUDInterface.h"

#include <SDL.h>


class GameScene : public IGameScene, public std::enable_shared_from_this<GameScene> {
public:
    void initialize() override {
        auto resourceManager = ServiceProvider::get<ResourceManager>();

        callbackTimer = std::make_unique<CallbackTimer>();

        auto backgroundLayer = std::make_shared<RenderLayer>();
        layers.push_back(backgroundLayer);
        auto playerLayer = std::make_shared<RenderLayer>();
        layers.push_back(playerLayer);
        auto UILayer = std::make_shared<RenderLayer>();
        layers.push_back(UILayer);

        collisionDetector = std::make_shared<CollisionDetector>();

        effectManager = std::make_shared<EffectManager>(playerLayer);
        asteroidManager = std::make_unique<AsteroidManager>(playerLayer, collisionDetector, effectManager);
        powerupManager = std::make_shared<PowerupManager>(playerLayer, collisionDetector);

        auto projectilePool = std::make_shared<ProjectilePool>(
                resourceManager->get<Shader>("rect"),
                playerLayer,
                collisionDetector
        );

        player = std::make_shared<Player>(
                glm::vec2(370, 450),  // Начальная позиция: центр внизу экрана
                glm::vec2(60, 60),
                resourceManager->get<Shader>("rectTextured"),
                resourceManager->get<Texture>("MainShip2"),
                projectilePool
        );
        player->setSpeed(250.f);
        player->setCenterPosition({400, 480});  // Центрируем по X, почти внизу по Y
        playerLayer->addObject(player);

        collisionDetector->addObject(player.get());


        auto background = std::make_shared<Object>(
                glm::vec2(0, 0),
                glm::vec2(800, 600),
                resourceManager->get<Shader>("blue_paper")
        );
        backgroundLayer->addObject(background);

        upgradeManager = std::make_unique<UpgradeManager>(player);
        hud = std::make_unique<HUDInterface>(UILayer, player);







        paused = false;
    }

    void activate() override {
        ServiceProvider::get<IRenderer>()->setActiveScene(shared_from_this());
    }

    void update(float timeDelta) override {
        if (!paused) {
            asteroidManager->update(timeDelta);
            effectManager->update(timeDelta);
            powerupManager->update(timeDelta);
            collisionDetector->checkCollisions();
            player->update(timeDelta);
            hud->update(timeDelta);
            callbackTimer->update();
            
            // Simple camera controls for testing (optional)
            updateCameraControls();
            
            if (player->getHealth() <= 0) {
                paused = true;
                hud->pause();
            }
        }
    }
    
    void updateCameraControls() {
        auto camera = ServiceProvider::get<Camera>();
        if (camera) {
            const Uint8* keyState = SDL_GetKeyboardState(nullptr);
            
            // Camera zoom controls (use = and - keys instead)
            if (keyState[SDL_SCANCODE_EQUALS] || keyState[SDL_SCANCODE_KP_PLUS]) {
                float currentZoom = camera->getViewMatrix()[0][0]; // Extract zoom from matrix
                camera->setZoom(std::min(currentZoom * 1.01f, 3.0f));
            }
            if (keyState[SDL_SCANCODE_MINUS] || keyState[SDL_SCANCODE_KP_MINUS]) {
                float currentZoom = camera->getViewMatrix()[0][0]; // Extract zoom from matrix  
                camera->setZoom(std::max(currentZoom * 0.99f, 0.5f));
            }
            
            // Camera pan controls (Arrow keys)
            glm::vec2 currentPos = glm::vec2(0, 0); // Would need getter in Camera for current position
            if (keyState[SDL_SCANCODE_LEFT]) {
                camera->setViewPosition(currentPos + glm::vec2(-2.0f, 0.0f));
            }
            if (keyState[SDL_SCANCODE_RIGHT]) {
                camera->setViewPosition(currentPos + glm::vec2(2.0f, 0.0f));
            }
            if (keyState[SDL_SCANCODE_UP]) {
                camera->setViewPosition(currentPos + glm::vec2(0.0f, -2.0f));
            }
            if (keyState[SDL_SCANCODE_DOWN]) {
                camera->setViewPosition(currentPos + glm::vec2(0.0f, 2.0f));
            }
        }
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
    std::unique_ptr<CallbackTimer> callbackTimer;
    std::unique_ptr<AsteroidManager> asteroidManager;
    std::shared_ptr<EffectManager> effectManager;
    std::shared_ptr<PowerupManager> powerupManager;
    std::shared_ptr<CollisionDetector> collisionDetector;
    std::unique_ptr<HUDInterface> hud;
    std::shared_ptr<Player> player;

    std::unique_ptr<UpgradeManager> upgradeManager;

    bool paused;
};


#endif //ENGINE_GAMESCENE_H
