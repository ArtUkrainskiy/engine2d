#ifndef INC_2DSDL_RENDERLAYER_H
#define INC_2DSDL_RENDERLAYER_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include "Object.h"
#include "TexturedObject.h"

class RenderLayer {
public:
    RenderLayer() = default;

    void addObject(const std::shared_ptr<Object> &object) {
        objects.push_back(object);
    }

    void removeObject(const std::shared_ptr<Object> &object) {
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

    void draw() {
        for (const auto& item : objects) {
            if (item != nullptr) {
                item->draw();
            }
        }

    }

private:
    std::vector<std::shared_ptr<Object>> objects;
};


#endif //INC_2DSDL_RENDERLAYER_H
