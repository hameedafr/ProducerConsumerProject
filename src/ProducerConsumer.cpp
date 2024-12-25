#include "ProducerConsumer.hpp"

ProducerConsumer::ProducerConsumer(size_t bufferSize, Logger& logger)
    : bufferSize(bufferSize), itemsProduced(0), itemsConsumed(0), logger(logger) {}

void ProducerConsumer::producer(int producerId) {
    while (true) {
        int item = rand() % 100 + 1; // Generate random item
        {
            std::unique_lock<std::mutex> lock(bufferMutex);
            bufferNotFull.wait(lock, [this]() { return buffer.size() < bufferSize; });

            buffer.push(item);
            ++itemsProduced;
            logger.log("Producer " + std::to_string(producerId) +
                       " produced item: " + std::to_string(item));
            logBufferState();
        }
        bufferNotEmpty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ProducerConsumer::consumer(int consumerId) {
    while (true) {
        int item;
        {
            std::unique_lock<std::mutex> lock(bufferMutex);
            bufferNotEmpty.wait(lock, [this]() { return !buffer.empty(); });

            item = buffer.front();
            buffer.pop();
            ++itemsConsumed;
            logger.log("Consumer " + std::to_string(consumerId) +
                       " consumed item: " + std::to_string(item));
            logBufferState();
        }
        bufferNotFull.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void ProducerConsumer::start(int numProducers, int numConsumers) {
    std::vector<std::thread> threads;
    for (int i = 0; i < numProducers; ++i) {
        threads.emplace_back(&ProducerConsumer::producer, this, i + 1);
    }
    for (int i = 0; i < numConsumers; ++i) {
        threads.emplace_back(&ProducerConsumer::consumer, this, i + 1);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

void ProducerConsumer::logBufferState() {
    logger.log("Buffer state: [");
    std::queue<int> temp = buffer;
    while (!temp.empty()) {
        logger.log(std::to_string(temp.front()) + " ");
        temp.pop();
    }
    logger.log("]");
}

