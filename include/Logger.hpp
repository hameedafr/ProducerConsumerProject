#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    explicit Logger(const std::string& filePath);
    ~Logger();
    void log(const std::string& message);

private:
    std::ofstream logFile;
    std::mutex logMutex;
};

#endif

