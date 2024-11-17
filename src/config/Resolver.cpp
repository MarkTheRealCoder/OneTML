//
// Created by marco on 17/11/2024.
//

#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include "Resolver.h"

using namespace std;
using namespace std::filesystem;
using namespace nlohmann;

Resolver* Resolver::instance = nullptr;

Resolver::Resolver(): GLOBAL_PATH(current_path().string()) {}

Resolver *Resolver::getInstance() {
    if (instance == nullptr) {
        instance = new Resolver();
    }
    return instance;
}

Resolver::~Resolver() {
    delete instance;
}

std::map<std::string, std::string> inspect_json(const json& data, const string& last_key = "") {
    std::map<std::string, std::string> config;
    for (auto& [key, value]: data.items()) {
        if (value.is_object()) {
            config.merge(inspect_json(value, key));
        } else {
            auto final_key = last_key.empty() || last_key == "constants" ? key : last_key + "." + key;
            config[final_key] = value;
        }
    }
    return config;
}

void Resolver::resolve() {
    std::string path = !(GLOBAL_PATH / CONFIG_FILE);
    cout << path << endl;
    ifstream configs(path);

    if (!configs.is_open()) {
        cerr << "Error: Could not open config file" << endl;
        exit(1);
    }

    json data;
    configs >> data;

    this->config.merge(inspect_json(data));
    cout << "Configurations: " << endl;
    for (auto& [key, value]: this->config) {
        cout << key << ": " << value << endl;
    }
}