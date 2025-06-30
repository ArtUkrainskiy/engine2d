//
// Created by artem on 12.06.24.
//

#ifndef ENGINE_SERVICEPROVIDER_H
#define ENGINE_SERVICEPROVIDER_H

#include <memory>
#include <unordered_map>
#include <typeindex>


class ServiceProvider {
public:
    template<typename T>
    static void provide(T *service) {
        services[typeid(T)] = service;
    }

    template<typename T>
    static T *get() {
        auto it = services.find(typeid(T));
        if (it != services.end()) {
            return static_cast<T *>(it->second);
        } else {
            return nullptr;
        }
    }

private:
    static std::unordered_map<std::type_index, void *> services;

};

#endif //ENGINE_SERVICEPROVIDER_H
