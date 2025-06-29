//
// Created by artem on 29.05.24.
//


#include "../graphics/Window.h"
#include "../graphics/Renderer.h"
#include "../utils/Utils.h"
#include "../game/EffectObject.h"
#include "../game/EffectManager.h"
#include "../core/Engine.h"
#include "../UI/UIBuilder.h"


int main() {
    auto engine = new Engine();
    const auto window = engine->createWindow<Window>(1600, 900);
    engine->createRenderer<Renderer>();
    auto resourceManager = engine->createResourceManager();
    resourceManager->loadResources("shaders");
    resourceManager->loadResources("img");
    resourceManager->loadResources("fonts");

    engine->createEventDispatcher();
    auto sceneManager = engine->createSceneManager();
    
    // Initialize camera with window size
    engine->createCamera(window->getWindowSize());

    auto scene = sceneManager->createScene<Scene>();
    sceneManager->activate<Scene>();

    auto layer = std::make_shared<RenderLayer>();

    scene->addRenderLayer(layer);

    auto effectManager = std::make_shared<EffectManager>(layer);


    auto button = UIBuilder::createButton(glm::vec2(100,100), glm::vec2(100,100), "SIMPLE", {1,1,1,1});
    layer->addObject(button);

    while(engine->update()){
        effectManager->update(1);
    }

    return 0;
}