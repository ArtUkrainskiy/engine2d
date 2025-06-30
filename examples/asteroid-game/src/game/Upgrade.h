//
// Created by artem on 27.06.24.
//

#ifndef ENGINE_UPGRADE_H
#define ENGINE_UPGRADE_H

#include <string>
#include <vector>
#include <memory>
#include <functional>

class Upgrade {
public:
    Upgrade(const std::string &name, const std::function<void()> &effect)
            : name(name), applyEffect(effect) {};

    std::string getName() {
        return name;
    }

    void addChild(const std::shared_ptr<Upgrade> &child) {
        children.push_back(child);
    }

    std::vector<std::shared_ptr<Upgrade>> getChildren() {
        return children;
    }

    bool isApplied() const {
        return applied;
    }

    void setApplied(bool newApplied) {
        applied = newApplied;
    }

    std::function<void()> getEffect() {
        return applyEffect;
    }


private:
    std::string name;
    std::function<void()> applyEffect;
    std::vector<std::shared_ptr<Upgrade>> children;
    bool applied = false;
};

#endif //ENGINE_UPGRADE_H
