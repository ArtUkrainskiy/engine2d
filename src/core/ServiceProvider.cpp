//
// Created by artem on 12.06.24.
//

#include "ServiceProvider.h"

std::unordered_map<std::type_index, void*> ServiceProvider::services;