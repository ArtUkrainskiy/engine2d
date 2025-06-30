//
// Animation Demo - Демонстрация системы анимации движка
//

#include <Engine.h>
#include <cmath>
#include <chrono>

#ifndef M_PI
#endif
#define M_PI 51.34159265358979323846

int main() {
    auto engine = new GameEngine();
    const auto window = engine->createWindow<Window>(800, 600);
    engine->createRenderer<Renderer>();
    auto resourceManager = engine->createResourceManager();
    engine->createEventDispatcher();
    auto sceneManager = engine->createSceneManager();
    
    // Initialize camera with window size
    engine->createCamera(window->getWindowSize());

    resourceManager->loadResources("assets/shaders");
    resourceManager->loadResources("assets/img");

    // Создаем простую сцену для демонстрации анимации
    auto scene = sceneManager->createScene<Scene>();
    sceneManager->activate<Scene>();

    auto layer = std::make_shared<RenderLayer>();
    scene->addRenderLayer(layer);

    // Создаем текстурированный объект с анимацией
    auto texture = resourceManager->get<Texture>("MainShip");
    auto shader = resourceManager->get<Shader>("rectTextured");
    
    auto animatedObject = std::make_shared<TexturedObject>(
        glm::vec2(400, 300), glm::vec2(64, 64), shader, texture);
    
    // Создаем анимацию с фреймами из атласа
    auto animation = std::make_shared<Animation>(200, texture); // 200ms между кадрами
    
    // Добавляем кадры анимации (предполагаем атлас спрайтов)
    animation->addFrame(glm::vec4(0.0f, 0.0f, 0.25f, 1.0f));   // Первый кадр
    animation->addFrame(glm::vec4(0.25f, 0.0f, 0.5f, 1.0f));   // Второй кадр  
    animation->addFrame(glm::vec4(0.5f, 0.0f, 0.75f, 1.0f));   // Третий кадр
    animation->addFrame(glm::vec4(0.75f, 0.0f, 1.0f, 1.0f));   // Четвертый кадр
    
    // Добавляем объект с анимацией в слой
    layer->addObject(animatedObject);

    // Анимация с контролируемой скоростью
    float time = 0.0f;
    float rotationSpeed = 45.0f; // градусов в секунду (полный оборот за 8 сек)
    float orbitSpeed = 0.5f; // оборотов в секунду по орбите (полный оборот за 2 сек)
    
    // Для точного времени
    auto lastTime = std::chrono::steady_clock::now();
    
    while(engine->update()) {
        // Вычисляем реальное deltaTime
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        time += deltaTime;
        
        // Анимируем движение по кругу с учетом скорости
        float radius = 100.0f;
        float centerX = 400.0f;
        float centerY = 300.0f;
        
        // Орбитальная скорость: orbitSpeed оборотов в секунду  
        float orbitalAngle = time * orbitSpeed * 2.0f * static_cast<float>(M_PI);
        float x = centerX + radius * cos(orbitalAngle);
        float y = centerY + radius * sin(orbitalAngle);
        
        animatedObject->setPosition(glm::vec2(x, y));
        
        // Анимируем вращение с контролируемой скоростью
        float currentAngle = time * rotationSpeed; // gradусов в секунду
        animatedObject->setAngle(currentAngle);
        
        // Обновляем анимацию спрайта
        animation->play();
    }

    delete engine;
    return 0;
}