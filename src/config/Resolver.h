//
// Created by marco on 17/11/2024.
//

#ifndef ONETML_RESOLVER_H
#define ONETML_RESOLVER_H

#include <map>
#include <utility>
#include "Path.h"


constexpr const char CONFIG_FILE[] = "onetml.config.json";

class Resolver {
private:
    static Resolver *instance;
    mutable Path GLOBAL_PATH;
    Resolver();

    std::map<std::string, std::string> config;
public:
    ~Resolver();
    static Resolver *getInstance();

    void resolve();
    Resolver(const Resolver&) = delete;
    Resolver& operator=(const Resolver&) = delete;
};


#endif //ONETML_RESOLVER_H
