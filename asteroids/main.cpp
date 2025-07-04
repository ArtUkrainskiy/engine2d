//
// Created by artem.ukrainskiy on 02.07.25.
//


#include <Engine.h>

#include "../examples/asteroid-game/src/game/ProjectileObject.h"
#include "graphics/BatchObject.h"
#include "graphics/InstancedBatchObject.h"

class VoidRenderer final : public IRenderer {
public:
    void init() override {};
    void draw() override {};
};

class VoidWindow final : public IWindow {
public:
    VoidWindow(int width, int height, const std::string& title) {}

    bool update() override {
        return true;
    };

    int init() override {
        return 1;
    };

    InputHandler* getInputHandler() override {
        return nullptr;
    };

    glm::vec2 getWindowSize() override {
        return {0, 0};
    };
};

class MainScene final : public IGameScene {
public:
    void activate() override {};
    void update(float timeDelta) override {};
    void deactivate() override {};
    void destroy() override {};

    void render(float timeDelta) override {
        for (const auto& layer : layers) {
            layer->draw();
        }
    };
};

class ObjectFactory {};

using WindowImpl = SDL2Window;
using RendererImpl = Renderer;

int main() {
    const auto engine = std::make_unique<GameEngine>();
    const auto window = engine->createWindow<WindowImpl>(800, 600, std::string("Asteroids"));
    engine->createRenderer<RendererImpl>();
    const auto resourceManager = engine->createResourceManager();
    engine->createEventDispatcher();
    const auto sceneManager = engine->createSceneManager();

    sceneManager->createScene<MainScene>();
    sceneManager->activateScene<MainScene>();
    // Initialize camera with window size
    engine->createCamera(window->getWindowSize());


    resourceManager->loadResources("assets/shaders");
    resourceManager->loadResources("assets/img");
    resourceManager->loadResources("assets/fonts");

    const auto layer = std::make_shared<RenderLayer>();
    layer->addObject(std::make_shared<TexturedObject>(
        glm::vec2(350, 250),
        glm::vec2(100, 100),
        resourceManager->get<Shader>("rectTextured"),
        resourceManager->get<Texture>("MainShip")
    ));

    // layer->addObject(std::make_shared<WireObject>(
    //     glm::vec2(350, 250),
    //     glm::vec2(100, 100),
    //     resourceManager->get<Shader>("rect"),
    //     glm::vec4(1, 0, 0, .20)
    // ));

    // Disable instanced rendering for now - test regular BatchObject instead
    auto batch = std::make_shared<BatchObject>(resourceManager->get<Shader>("rect"));

    std::vector<std::shared_ptr<Object>> objects;

    for (int i = 0; i < 100; ++i) {
        float x = rand() % 1600;
        float y = rand() % 900;
        float size = 25 + rand() % 30; // Size between 25-55
        float r = (rand() % 100) / 100.0f;
        float g = (rand() % 100) / 100.0f;
        float b = (rand() % 100) / 100.0f;

        auto obj = std::make_shared<WireObject>(
            glm::vec2(x, y),
            glm::vec2(size, size),
            resourceManager->get<Shader>("rect"),
            glm::vec4(r, g, b, .2)
            // resourceManager->get<Texture>("MainShip")
        );

        obj->setAngle(rand() % 360);

        objects.push_back(obj);
        // layer->addObject(obj);
        batch->addObject(obj);
    }

    layer->addObject(batch);
    sceneManager->getActiveScene()->addRenderLayer(layer);


    while (engine->update()) {
        // batch->makeDirty();
    }

    return 0;
}
