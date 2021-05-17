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
#include "logger.h"
#include "logmanager.h"

// These macros only work in scope of a LogSource class (or derived)
#define TRC_FATAL(text) _log(__FILE__, __LINE__, base::TRC_LEVEL_FATAL, text)
#define TRC_ERROR(text) _log(__FILE__, __LINE__, base::TRC_LEVEL_ERROR, text)
#define TRC_WARN(text) _log(__FILE__, __LINE__, base::TRC_LEVEL_WARN, text)
#define TRC_INFO(text) _log(__FILE__, __LINE__, base::TRC_LEVEL_INFO, text)
#define TRC_DEBUG(text) _log(__FILE__, __LINE__, base::TRC_LEVEL_DEBUG, text)
#define TRC_TRACE(text) _log(__FILE__, __LINE__, base::TRC_LEVEL_TRACE, text)
#define TRC_SCOPED(text) base::ScopedLogLogger _scope(*this, text)
#define TRC_SCOPED_FUNC() base::ScopedLogLogger _scope(*this, __PRETTY_FUNCTION__)

// Outside of LogSource class these macros can be used but a pointer to a
// Logger needs to be provided manually
#define TRC_LOGGER_FATAL(logger, text) logger->log(__FILE__, __LINE__, base::TRC_LEVEL_FATAL, text)
#define TRC_LOGGER_ERROR(logger, text) logger->log(__FILE__, __LINE__, base::TRC_LEVEL_ERROR, text)
#define TRC_LOGGER_WARN(logger, text) logger->log(__FILE__, __LINE__, base::TRC_LEVEL_WARN, text)
#define TRC_LOGGER_INFO(logger, text) logger->log(__FILE__, __LINE__, base::TRC_LEVEL_INFO, text)
#define TRC_LOGGER_DEBUG(logger, text) logger->log(__FILE__, __LINE__, base::TRC_LEVEL_DEBUG, text)
#define TRC_LOGGER_TRACE(logger, text) logger->log(__FILE__, __LINE__, base::TRC_LEVEL_TRACE, text)
#define TRC_LOGGER_SCOPED(logger, text) base::ScopedLogLogger _scope(logger, text)
#define TRC_LOGGER_SCOPED_FUNC(logger) base::ScopedLogLogger _scope(logger, __PRETTY_FUNCTION__)

namespace base {
class LogSource {
   public:
    LogSource(std::string name) : _logger(LogManager::instance().getLogger(name)) {}

    void _log(std::string filename, uint32_t line, uint8_t level, std::string trace) const {
        _logger->log(filename, line, level, trace);
    }

    void _log(uint8_t level, std::string trace) const { _logger->log(level, trace); }

    const std::shared_ptr<Logger>& _getLogger() const { return _logger; }

   private:
    std::shared_ptr<Logger> _logger;
};

class ScopedLogLogger {
   public:
    ScopedLogLogger(const LogSource& src, std::string text) : _logger(src._getLogger()), _text(text) {
        entryTrace();
        //++_instances;
    }
    ScopedLogLogger(std::shared_ptr<Logger> logger, std::string text) : _logger(logger), _text(text) {
        entryTrace();
        //++_instances;
    }

    ~ScopedLogLogger() {
        //--_instances;
        exitTrace();
    }

   private:
    void entryTrace() {
        _logger->log(TRC_LEVEL_TRACE,
                     /*std::string(_instances * 2, ' ') + */ std::string("--> ") + _text);
    }
    void exitTrace() {
        _logger->log(TRC_LEVEL_TRACE,
                     /*std::string(_instances * 2, ' ') + */ std::string("<-- ") + _text);
    }
    const std::shared_ptr<Logger> _logger;
    std::string _text;
    // static int32_t _instances;
};
}  // namespace base
