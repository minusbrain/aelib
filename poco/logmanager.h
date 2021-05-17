/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <map>
#include <memory>

#include "logger.h"

namespace base {
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
}  // namespace base
