#include "ProducerConsumer.hpp"
#include "Logger.hpp"
#include "ConfigManager.hpp"

int main() {
    try {
        ConfigManager config("config/config.txt");
        Logger logger("logs/log.txt");

        size_t bufferSize = config.getValue("BufferSize");
        int numProducers = config.getValue("NumProducers");
        int numConsumers = config.getValue("NumConsumers");

        ProducerConsumer pc(bufferSize, logger);
        pc.start(numProducers, numConsumers);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}

