//
// Created by artem on 29.05.24.
//


#include "../graphics/Window.h"
#include "../graphics/Renderer.h"

#include "../core/Engine.h"

#include "MenuScene.h"
#include "GameScene.h"
#include "ScoreScene.h"


int main() {
    auto engine = new Engine();
    const auto window = engine->createWindow<Window>(800, 600);
    engine->createRenderer<Renderer>();
    auto resourceManager = engine->createResourceManager();
    engine->createEventDispatcher();
    auto sceneManager = engine->createSceneManager();
    
    // Initialize camera with window size
    engine->createCamera(window->getWindowSize());

    engine->createService<ScoreManager>();

    resourceManager->loadResources("shaders");
    resourceManager->loadResources("img");
    resourceManager->loadResources("fonts");

    sceneManager->createScene<MenuScene>();
    sceneManager->createScene<GameScene>();
    sceneManager->createScene<ScoreScene>();


    sceneManager->activate<MenuScene>();


    while(engine->update()){
    }

    return 0;
}