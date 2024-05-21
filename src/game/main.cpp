#include "../graphics/Window.h"
#include "../physics/CollisionDetector.h"
#include "../utils/Utils.h"
#include "../graphics/TextRenderer.h"
#include "Player.h"
#include "../core/InputHandler.h"
#include "../graphics/WireObject.h"
#include "../graphics/Renderer.h"
#include "AsteroidFactory.h"
#include "AsteroidManager.h"
#include "../utils/CallbackTimer.h"
#include "../UI/Button.h"
#include "PowerupFactory.h"
#include "PowerupManager.h"
#include "EnemyObject.h"

int main(int argc, char *argv[]) {
    auto window = new Window(800, 600);
    window->init();
    InputHandler inputHandler;
    inputHandler.addObserver(window);

    auto collitionDetector = std::make_shared<CollisionDetector>();

    auto text = std::make_shared<TextRenderer>("fonts/OpenSans-Regular.ttf", 16);


    auto renderer = std::make_unique<Renderer>();
    auto scene = std::make_shared<Scene>();
    auto backgroundLayer = std::make_shared<RenderLayer>();
    auto playerLayer = std::make_shared<RenderLayer>();
    auto uiLayer = std::make_shared<RenderLayer>();

    renderer->setScene(scene);

    scene->addRenderLayer(backgroundLayer);
    scene->addRenderLayer(playerLayer);
    scene->addRenderLayer(uiLayer);


    auto menuScene = std::make_shared<Scene>();
    auto menuLayer = std::make_shared<RenderLayer>();
    menuScene->addRenderLayer(menuLayer);
    renderer->setScene(menuScene);

    auto shader = std::make_shared<Shader>(Utils::readFile("shaders/tilemap.vert"),
                                           Utils::readFile("shaders/tilemap.frag"));
    auto shader2 = std::make_shared<Shader>(Utils::readFile("shaders/rect.vert"),
                                            Utils::readFile("shaders/rect.frag"));
    auto textured = std::make_shared<Shader>(Utils::readFile("shaders/rectTextured.vert"),
                                             Utils::readFile("shaders/rectTextured.frag"));
    auto bluePaper = std::make_shared<Shader>(Utils::readFile("shaders/blue_paper.vert"),
                                              Utils::readFile("shaders/blue_paper.frag"));

    shader2->setUniform("col", glm::vec4(0, 0, 0, 1));
    shader2->setUniform("projection", glm::ortho(0.0f, (float) 800, (float) 600, 0.0f,
                                                 -1.0f, 1.0f));
    textured->setUniform("projection", glm::ortho(0.0f, (float) 800, (float) 600, 0.0f,
                                                  -1.0f, 1.0f));
    bluePaper->setUniform("projection", glm::ortho(0.0f, (float) 800, (float) 600, 0.0f,
                                                   -1.0f, 1.0f));

    auto background = std::make_shared<Object>(glm::vec2(0, 0), glm::vec2(800, 600), bluePaper);
    backgroundLayer->addObject(background);


    auto projectilePool = std::make_shared<ProjectilePool>(shader2, playerLayer, collitionDetector);

    auto texture = std::make_shared<Texture>("img/MainShip2.png");
    auto player = std::make_shared<Player>(
            glm::vec2(400, 300),
            glm::vec2(60, 60),
            textured, texture,
            projectilePool
    );

    player->setName("player");
    player->setSpeed(250.f);
//    player->setCollisionDetector(collitionDetector);
    player->setCenterPosition({400, 300});
    collitionDetector->addObject(player.get());
    playerLayer->addObject(player);


    auto textTexture = text->renderText("FPS: " + std::to_string(0), 0, 0, {255, 255, 255, 0});
    auto fpsText = std::make_shared<TexturedObject>(glm::vec2(5, 5), textTexture->getSize(), textured, textTexture);
    uiLayer->addObject(fpsText);

    auto hpTexture = text->renderText("HEALTH: " + std::to_string(100) + "%", 0, 0, {255, 255, 255, 0});
    auto hpText = std::make_shared<TexturedObject>(glm::vec2(350, 550), hpTexture->getSize(), textured, hpTexture);
    uiLayer->addObject(hpText);


    auto smallTexture = std::make_shared<Texture>("img/asteroid2.png");
    auto mediumTexture = std::make_shared<Texture>("img/asteroid3.png");
    auto LargeTexture = std::make_shared<Texture>("img/asteroid4.png");
    auto asteroidManager = std::make_shared<AsteroidManager>(playerLayer, collitionDetector);
    auto factory = new AsteroidFactory();
    factory->setSpawnArea(glm::vec4(0, -150, 800, -150));
    factory->setTargetArea(glm::vec4(-50, 650, 850, 650));
    factory->addPrototype(
            AsteroidPrototype::SMALL,
            std::make_shared<AsteroidPrototype>(smallTexture, textured, std::make_pair(35, 50),
                                                std::make_pair(50.f, 350.f))
    );
    factory->addPrototype(
            AsteroidPrototype::MEDIUM,
            std::make_shared<AsteroidPrototype>(mediumTexture, textured, std::make_pair(45, 75),
                                                std::make_pair(30.f, 250.f))
    );
    factory->addPrototype(
            AsteroidPrototype::LARGE,
            std::make_shared<AsteroidPrototype>(LargeTexture, textured, std::make_pair(50, 100),
                                                std::make_pair(25.f, 150.f))
    );

    auto callbackTimer = std::make_unique<CallbackTimer>();
    // Таймер спавнит астероиды раз в 300мс
    callbackTimer->addCallback(
            [&asteroidManager, &factory]() { asteroidManager->addObject(factory->build(AsteroidPrototype::SMALL)); },
            300 * 2);

    callbackTimer->addCallback(
            [&asteroidManager, &factory]() { asteroidManager->addObject(factory->build(AsteroidPrototype::MEDIUM)); },
            500 * 2);

    callbackTimer->addCallback(
            [&asteroidManager, &factory]() { asteroidManager->addObject(factory->build(AsteroidPrototype::LARGE)); },
            750 * 2);


    auto bgTexture = std::make_shared<Texture>("img/background.png");
    auto menuBackground = std::make_shared<TexturedObject>(glm::vec2(0, 0), glm::vec2(800, 600), textured, bgTexture);
    menuLayer->addObject(menuBackground);

    auto repairTexture = std::make_shared<Texture>("img/repair_bonus.png");
    auto weaponTexture = std::make_shared<Texture>("img/weapon_upgrade.png");

    auto powerupFactory = new PowerupFactory();
    auto powerupManager = new PowerupManager(playerLayer, collitionDetector);
    powerupFactory->setSpawnArea(glm::vec4(0, -150, 800, -150));
    powerupFactory->addPrototype(PowerupPrototype::REPAIR_BONUS, std::move(
            std::make_unique<PowerupPrototype>(repairTexture, textured, PowerupPrototype::REPAIR_BONUS)));
    powerupFactory->addPrototype(PowerupPrototype::WEAPON_UPGRADE, std::move(
            std::make_unique<PowerupPrototype>(weaponTexture, textured, PowerupPrototype::WEAPON_UPGRADE)));

    callbackTimer->addCallback(
            [&powerupManager, &powerupFactory]() {
                powerupManager->addObject(powerupFactory->build(PowerupPrototype::REPAIR_BONUS));
            },
            7000);

    callbackTimer->addCallback(
            [&powerupManager, &powerupFactory]() {
                powerupManager->addObject(powerupFactory->build(PowerupPrototype::WEAPON_UPGRADE));
            },
            9000);


    auto playButton = std::make_shared<Button>(glm::vec2(600, 365), glm::vec2(180, 45), shader2, glm::vec4{1, 1, 1, 1});
    auto playTexture = text->renderText("Play", 0, 0, {255, 255, 255, 0});
    auto playObject = std::make_shared<TexturedObject>(playButton->getCenterPosition(), textTexture->getSize(),
                                                       textured, playTexture);
    playObject->setCenterPosition(playButton->getCenterPosition());
    menuLayer->addObject(playObject);
    menuLayer->addObject(playButton);

    {
        auto enemyTexture = std::make_shared<Texture>("img/enemy1.png");
        auto enemyObject = std::make_shared<EnemyObject>(glm::vec2{1, 1}, glm::vec2(50, 50), textured, enemyTexture);
        enemyObject->setCenterPosition({400, 100});
        enemyObject->setAngle(180);
        playerLayer->addObject(enemyObject);
    }
    {
        auto enemyTexture = std::make_shared<Texture>("img/enemy1.png");
        auto enemyObject = std::make_shared<EnemyObject>(glm::vec2{1, 1}, glm::vec2(50, 50), textured, enemyTexture);
        enemyObject->setCenterPosition({300, 100});
        enemyObject->setAngle(180);
        playerLayer->addObject(enemyObject);
    }
    {
        auto enemyTexture = std::make_shared<Texture>("img/enemy1.png");
        auto enemyObject = std::make_shared<EnemyObject>(glm::vec2{1, 1}, glm::vec2(50, 50), textured, enemyTexture);
        enemyObject->setCenterPosition({500, 100});
        enemyObject->setAngle(180);
        playerLayer->addObject(enemyObject);
    }

    bool play = false;
    playButton->onClick([&play, &renderer, scene]() {
        play = true;
        renderer->setScene(scene);

    });

    inputHandler.addObserver(playButton.get());

    int frameCount = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastTimeDelta = SDL_GetTicks();
    Uint32 currentTime = 0;
    float deltaTime = 0;
    do {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTimeDelta) / 1000.0f;

        inputHandler.handleInput();

        if (play) {
            collitionDetector->checkCollisions();
            player->update(deltaTime);
            hpTexture = text->renderText("HEALTH: " + std::to_string(player->getHealth()) + "%", 0, 0,
                                         {255, 255, 255, 0});
            hpText->setTexture(hpTexture);
            callbackTimer->update();
            asteroidManager->update(deltaTime);
            powerupManager->update(deltaTime);
        }

        renderer->draw();
        frameCount++;
        if (currentTime - lastTime >= 1000) {
            std::cout << "FPS: " << frameCount << std::endl;
            textTexture = text->renderText("FPS: " + std::to_string(frameCount), 0, 0, {255, 255, 255, 255});
            fpsText->setTexture(textTexture);
            frameCount = 0;
            lastTime = currentTime;
        }
        lastTimeDelta = currentTime;
    } while (window->update());

    return 0;
}