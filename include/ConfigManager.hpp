#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>
#include <unordered_map>

class ConfigManager {
public:
    explicit ConfigManager(const std::string& filePath);
    int getValue(const std::string& key);

private:
    std::unordered_map<std::string, int> configMap;
    void parseConfig(const std::string& filePath);
};

#endif

