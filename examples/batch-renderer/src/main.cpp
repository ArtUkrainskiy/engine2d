//
// Created by artem.ukrainskiy on 27.06.25.
//

#include "BatchedObject.h"
#include <cmath>
#include <Engine.h>

int main(int argc, char* argv[]) {
    const auto engine = new GameEngine();
    const auto window = engine->createWindow<Window>(1600, 900);
    engine->createRenderer<Renderer>();

    const auto resourceManager = engine->createResourceManager();
    resourceManager->loadResources("assets/shaders");
    resourceManager->loadResources("assets/img");
    resourceManager->loadResources("assets/fonts");

    engine->createEventDispatcher();
    const auto sceneManager = engine->createSceneManager();
    
    // Initialize camera with window size
    engine->createCamera(window->getWindowSize());

    const auto scene = sceneManager->createScene<Scene>();
    const auto layer = std::make_shared<RenderLayer>();
    scene->addRenderLayer(layer);


    sceneManager->activate<Scene>();


    auto ship = std::make_shared<TexturedObject>(
        glm::vec2(500, 500),
        glm::vec2(100, 100),
        resourceManager->get<Shader>("rectTextured"),
        resourceManager->get<Texture>("MainShip")
    );
    // resourceManager->get<Shader>("rect")->setUniform("col", {1.0f, 1.0f, 1.0f, 1.0f});


    // Create BatchedObject with a simple wrapper that integrates with Object system
    class SimpleBatchRenderer : public Object {
    public:
        SimpleBatchRenderer(std::shared_ptr<BatchedObject> batcher)
            : Object({0, 0}, {0, 0}, nullptr), batchRenderer(batcher) {}

        void draw() override {
            // Update projection matrix before drawing
            if (const auto camera = ServiceProvider::get<Camera>()) {
                batchRenderer->setProjectionMatrix(camera->getViewProjectionMatrix());
            }
            batchRenderer->draw();
        }

        std::shared_ptr<BatchedObject> batchRenderer;
    };

    auto batchRenderer = std::make_shared<BatchedObject>(resourceManager->get<Shader>("batched"));
    auto batchWrapper = std::make_shared<SimpleBatchRenderer>(batchRenderer);
    
    layer->addObject(batchWrapper);
    layer->addObject(ship);

    // Benchmark: Create 100000 objects for performance testing using indices
    std::vector<size_t> objectIndices;
    objectIndices.reserve(200000);

    // Initialize random seed
    srand(time(nullptr));
    std::cout << "Random number generator seed: " << rand() << std::endl;
    for (int i = 0; i < 200000; i++) {
        float x = rand() % 1600;
        float y = rand() % 900;
        float size = 5 + rand() % 15; // Size between 5-20
        float r = (rand() % 100) / 100.0f;
        float g = (rand() % 100) / 100.0f;
        float b = (rand() % 100) / 100.0f;

        auto obj = batchRenderer->addInstance({x, y}, {size, size}, {r, g, b, 1.0f});
        objectIndices.push_back(obj->getIndex());
    }

    auto start = std::chrono::high_resolution_clock::now();
    int frames = 0;

    // Create animation variables
    float time = 0.0f;
    std::cout << "Rendering " << objectIndices.size() << " objects" << std::endl;
    int i = 0;
    while (engine->update()) {
        // Objects are now drawn automatically by the engine through RenderLayer
        frames++;
        if (frames % 1000 == 0) {
            auto now = std::chrono::high_resolution_clock::now();
            auto ms = std::chrono::duration<double, std::milli>(now - start).count();
            std::cout << "Real FPS: " << (frames * 1000.0 / ms) << std::endl;
            start = now;
            frames = 0;
        }


        i++;
        // continue;
        if (i % 60 != 0) {
            continue;
        }
        time += 0.016f; // Assume 60 FPS

        // Move all 100000 objects randomly using direct batch update
        for (size_t index : objectIndices) {
            // Direct access to instance data for better performance
            float newX = static_cast<float>(rand() % 1600);
            float newY = static_cast<float>(rand() % 900);

            // Keep objects within screen bounds (unnecessary since we're setting to screen bounds)
            newX = std::max(0.0f, std::min(1600.0f, newX));
            newY = std::max(0.0f, std::min(900.0f, newY));

            // Get random color for visual effect
            float r = static_cast<float>(rand() % 100) / 100.0f;
            float g = static_cast<float>(rand() % 100) / 100.0f;
            float b = static_cast<float>(rand() % 100) / 100.0f;

            batchRenderer->updateInstance(index, {newX, newY}, {10, 10}, {r, g, b, 1.0f});
        }
    }

    return 0;
}
