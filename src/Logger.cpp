#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

Logger::Logger(const std::string& filePath) {
    logFile.open(filePath, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file!");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    logFile << std::ctime(&time) << ": " << message << std::endl;
}

