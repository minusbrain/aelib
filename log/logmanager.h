#pragma once

#include <map>
#include <memory>

#include "logger.h"

namespace ae {
class LogManager {
  public:
    static LogManager& instance() {
        static LogManager inst;
        return inst;
    }

    std::shared_ptr<Logger> getLogger(std::string name) {
        auto it = _loggerMap.find(name);

        if (it != _loggerMap.end()) {
            return it->second;
        }
        std::shared_ptr<Logger> logger(new Logger(name));
        logger->setLogLevel(_globalLogLevel);
        _loggerMap.emplace(name, logger);
        return logger;
    }

    void setLogLevel(std::string name, uint8_t level) {
        auto logger = getLogger(name);

        logger->setLogLevel(level);
    }

    void setLogLevel(uint8_t level) {
        _globalLogLevel = level;
        for (auto& logger : _loggerMap) {
            logger.second->setLogLevel(level);
        }
    }

    ~LogManager(){};

  private:
    LogManager() : _loggerMap(), _globalLogLevel(TRC_LEVEL_ERROR) {}

    std::map<std::string, std::shared_ptr<Logger>> _loggerMap;
    uint8_t _globalLogLevel;
};
}
