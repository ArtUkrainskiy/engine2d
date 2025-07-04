cmake_minimum_required(VERSION 3.22)
project(AsteroidGame)

add_executable(AsteroidGame
    src/main.cpp
    
    # Game objects
    src/game/Player.cpp
    src/game/PlayerShip.cpp
    src/game/AsteroidObject.cpp
    src/game/ProjectileObject.cpp
    src/game/PowerupObject.cpp
    src/game/EnemyObject.cpp
    src/game/EffectObject.cpp
    
    # Managers
    src/game/AsteroidManager.cpp
    src/game/PowerupManager.cpp
    src/game/EnemyManager.cpp
    src/game/EffectManager.cpp
    
    # Factories and Prototypes
    src/game/AsteroidFactory.cpp
    src/game/AsteroidPrototype.cpp
    src/game/PowerupFactory.cpp
    src/game/PowerupPrototype.cpp
    src/game/EffectFactory.cpp
    src/game/EffectPrototype.cpp
    
    # Pools and Utils
    src/game/ProjectilePool.cpp
    src/game/GameEvent.cpp
    src/game/GameMaster.cpp
    src/game/MenuScene.cpp
    
    # Game-specific core components
    src/game/ScoreManager.cpp
    src/game/Upgrade.cpp
    src/game/UpgradeManager.cpp
    src/game/UpgradeTree.cpp
)

target_link_libraries(AsteroidGame PRIVATE GameEngine)

# Копировать ресурсы
add_custom_command(TARGET AsteroidGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:AsteroidGame>/assets
)