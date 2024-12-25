#ifndef PRODUCER_CONSUMER_HPP
#define PRODUCER_CONSUMER_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <iostream>
#include <chrono>
#include <atomic>

#include "Logger.hpp"

class ProducerConsumer {
public:
    ProducerConsumer(size_t bufferSize, Logger& logger);
    void producer(int producerId);
    void consumer(int consumerId);
    void start(int numProducers, int numConsumers);

private:
    size_t bufferSize;
    std::queue<int> buffer;
    std::mutex bufferMutex;
    std::condition_variable bufferNotEmpty;
    std::condition_variable bufferNotFull;
    std::atomic<int> itemsProduced;
    std::atomic<int> itemsConsumed;
    Logger& logger;

    void logBufferState();
};

#endif

