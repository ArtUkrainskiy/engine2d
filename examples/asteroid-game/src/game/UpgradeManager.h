//
// Created by artem on 28.06.24.
//

#ifndef ENGINE_UPGRADEMANAGER_H
#define ENGINE_UPGRADEMANAGER_H


#include <memory>
#include <array>
#include "../game/Player.h"
#include "UpgradeTree.h"

class UpgradeManager {
public:
    explicit UpgradeManager(const std::shared_ptr<Player> &player) {
        eventDispatcher = ServiceProvider::get<EventDispatcher>();
        listenerId = eventDispatcher->registerListener(
                EventDispatcher::EVENT_SCORE_REACHED,
                [this](EventDispatcher::EventType event, const std::shared_ptr<Object> &trigger) {
                    checkAvailableUpgrades();
                });
        scoreManager = ServiceProvider::get<ScoreManager>();
        auto root = std::make_shared<Upgrade>("root", nullptr);
        root->addChild(std::make_shared<Upgrade>("rate_of_fire", nullptr));
        root->addChild(std::make_shared<Upgrade>("ship_velocity", nullptr));

        upgradeTree = new UpgradeTree(root);
        nextGoal = upgradeScoreTable[upgradeIndex];

    }

    ~UpgradeManager() {
        if (eventDispatcher) {
            eventDispatcher->unregisterListener(EventDispatcher::EVENT_SCORE_REACHED, listenerId);
        }
        delete upgradeTree;
    }

    void checkAvailableUpgrades() {
        if(scoreManager->getScore() >= nextGoal){
            if(upgradeScoreTable.size() > upgradeIndex) {
                upgradeIndex++;
                nextGoal = upgradeScoreTable[upgradeIndex];
            }
            std::cout << "upgrade reached" << std::endl;
//            ServiceProvider::get<EventDispatcher>()->dispatch(EventDispatcher::EVENT_SCORE_REACHED, nullptr);
        }
    }



private:
    UpgradeTree *upgradeTree;
    ScoreManager *scoreManager;
    EventDispatcher *eventDispatcher;
    EventDispatcher::ListenerId listenerId;
    uint32_t nextGoal = 0;
    uint32_t upgradeIndex = 0;
    std::array<uint32_t, 10> upgradeScoreTable = {100, 300, 750, 1500, 3000, 5000, 10000, 25000, 50000, 100000};


};


#endif //ENGINE_UPGRADEMANAGER_H
