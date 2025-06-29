//
// Created by artem on 05.05.24.
//

#ifndef INC_2DSDL_PLAYER_H
#define INC_2DSDL_PLAYER_H

#include <SDL_events.h>
#include "../core/IEventObserver.h"
#include "../graphics/TexturedObject.h"
#include "../physics/PhysicObject.h"
#include "ProjectilePool.h"
#include "../utils/CallbackTimer.h"
#include "PowerupObject.h"
#include "PowerupPrototype.h"
#include "../core/ScoreManager.h"

class Player
        : public IEventObserver,
          public TexturedObject,
          public PhysicObject,
          public std::enable_shared_from_this<Player> {
public:
    Player(glm::vec2 pos, glm::vec2 size, const std::shared_ptr<Shader> &shader,
           const std::shared_ptr<Texture> &texture, const std::shared_ptr<ProjectilePool> &newProjectilePool)
            : TexturedObject(pos, size, shader, texture), projectilePool(newProjectilePool) {

        weaponTimer = std::make_unique<CallbackTimer>();
        weaponTimer->addCallback(
                [this, newProjectilePool]() { this->shoot(); },
                250);

    }

    void setSpeed(float_t newSpeed) {
        speed = newSpeed;
    }

    void update(float deltaTime) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
        auto offset = glm::vec2(0, 0);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            offset.y--;
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            offset.x--;
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            offset.y++;
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            offset.x++;
        }

        offset *= speed * deltaTime;
        this->translatePosition(offset);

        weaponTimer->update();
        projectilePool->update(deltaTime);

    }

    void shoot() {
        if (weapon > 1) {
            float angleStep = 15.0f; // Шаг между снарядами в градусах
            float startAngle =
                    -(weapon - 1) * angleStep / 2.0f; // Начальный угол, чтобы снаряды были симметрично распределены
            for (int i = 0; i < weapon; i++) {
                projectilePool->getProjectile(getCenterPosition(), startAngle + i * angleStep,
                                              ProjectileObject::PLAYER);
            }
        } else {
            projectilePool->getProjectile(getCenterPosition(), 0, ProjectileObject::PLAYER);
        }
    }

    void collide(Object *object) override {
        if (auto asteroid = dynamic_cast<AsteroidObject *>(object)) {
            asteroid->setAlive(false);
            health -= 10;
        }

        if (auto powerup = dynamic_cast<PowerupObject *>(object)) {
            powerup->setAlive(false);
            if (powerup->getType() == PowerupPrototype::REPAIR_BONUS) {
                health += 30;
            } else if (powerup->getType() == PowerupPrototype::WEAPON_UPGRADE) {
                weapon += 1;
                if (weapon > 12) {
                    weapon = 12;
                }
            }
        }

        if (auto projectile = dynamic_cast<ProjectileObject *>(object)) {
            if (projectile->getOwner() == ProjectileObject::ENEMY) {
                projectile->setAlive(false);
                health -= 5;
            }
        }
    }

    void onNotify(SDL_Event &event) override {

    }

    int getHealth() const {
        return health;
    }

private:
    int weapon = 1;

    std::shared_ptr<ProjectilePool> projectilePool;

    int health = 100;
    int score = 0;
    float_t speed = 100.f;

    std::unique_ptr<CallbackTimer> weaponTimer;
};

#endif //INC_2DSDL_PLAYER_H
