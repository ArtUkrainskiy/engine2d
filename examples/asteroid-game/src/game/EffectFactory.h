//
// Created by artem on 28.05.24.
//

#ifndef ENGINE_EFFECTFACTORY_H
#define ENGINE_EFFECTFACTORY_H


#include "EffectPrototype.h"

class EffectFactory {
public:
    void addPrototype(int type, std::unique_ptr<EffectPrototype> prototype){
        prototypes[type] = std::move(prototype);
    }

    std::shared_ptr<EffectObject> build(EffectObject::Type type, glm::vec2 position, glm::vec2 size){
        return prototypes[type]->clone(position, size);
    }


private:
    std::unique_ptr<EffectPrototype> prototypes[EffectObject::_COUNT];

};


#endif //ENGINE_EFFECTFACTORY_H
