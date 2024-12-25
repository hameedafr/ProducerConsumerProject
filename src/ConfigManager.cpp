#include "ConfigManager.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

ConfigManager::ConfigManager(const std::string& filePath) {
    parseConfig(filePath);
}

void ConfigManager::parseConfig(const std::string& filePath) {
    std::ifstream configFile(filePath);
    if (!configFile.is_open()) {
        throw std::runtime_error("Unable to open config file!");
    }
    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string key;
        int value;
        if (iss >> key >> value) {
            configMap[key] = value;
        }
    }
}

int ConfigManager::getValue(const std::string& key) {
    return configMap.at(key);
}

