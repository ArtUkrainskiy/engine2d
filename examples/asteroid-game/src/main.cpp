//
// Created by artem on 29.05.24.
//
#include "engine/Engine.h"

#include "scenes/MenuScene.h"
#include "scenes/GameScene.h"
#include "scenes/ScoreScene.h"


int main() {
    auto engine = new GameEngine();
    const auto window = engine->createWindow<Window>(800, 600);
    engine->createRenderer<Renderer>();
    auto resourceManager = engine->createResourceManager();
    engine->createEventDispatcher();
    auto sceneManager = engine->createSceneManager();
    
    // Initialize camera with window size
    engine->createCamera(window->getWindowSize());

    engine->createService<ScoreManager>();

    resourceManager->loadResources("assets/shaders");
    resourceManager->loadResources("assets/img");
    resourceManager->loadResources("assets/fonts");

    sceneManager->createScene<MenuScene>();
    sceneManager->createScene<GameScene>();
    sceneManager->createScene<ScoreScene>();


    sceneManager->activate<MenuScene>();


    while(engine->update()){
    }

    return 0;
}