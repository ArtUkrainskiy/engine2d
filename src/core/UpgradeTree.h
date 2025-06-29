//
// Created by artem on 28.06.24.
//

#ifndef ENGINE_UPGRADETREE_H
#define ENGINE_UPGRADETREE_H


#include <memory>
#include <random>
#include "Upgrade.h"

class UpgradeTree {
public:
    UpgradeTree(std::shared_ptr<Upgrade> root) : root(root) {}

    void applyUpgrade(const std::string& upgradeName) {
        auto upgrade = findUpgrade(root, upgradeName);
        if (upgrade && !upgrade->isApplied()) {
            upgrade->getEffect()();
            upgrade->setApplied(true);
        }
    }

    bool isUpgradeApplied(const std::string& upgradeName) const {
        auto upgrade = findUpgrade(root, upgradeName);
        return upgrade && upgrade->isApplied();
    }

    std::vector<std::shared_ptr<Upgrade>> getRandomAvailableUpgrades(int n) {
        std::vector<std::shared_ptr<Upgrade>> availableUpgrades;
        getAvailableUpgrades(root, availableUpgrades);

        std::vector<std::shared_ptr<Upgrade>> randomUpgrades;
        std::sample(availableUpgrades.begin(), availableUpgrades.end(), std::back_inserter(randomUpgrades), n, std::mt19937{std::random_device{}()});
        return randomUpgrades;
    }

private:
    std::shared_ptr<Upgrade> root;

    std::shared_ptr<Upgrade> findUpgrade(std::shared_ptr<Upgrade> node, const std::string& name) const {
        if (node->getName() == name) {
            return node;
        }
        for (auto& child : node->getChildren()) {
            auto found = findUpgrade(child, name);
            if (found) {
                return found;
            }
        }
        return nullptr;
    }

    void getAvailableUpgrades(const std::shared_ptr<Upgrade>& node, std::vector<std::shared_ptr<Upgrade>>& availableUpgrades) const {
        if (!node->isApplied()) {
            availableUpgrades.push_back(node);
        }
        for (auto& child : node->getChildren()) {
            getAvailableUpgrades(child, availableUpgrades);
        }
    }
};


#endif //ENGINE_UPGRADETREE_H
