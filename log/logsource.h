#pragma once
#include "logger.h"
#include "logmanager.h"

// These macros only work in scope of a LogSource class (or derived)
#define TRC_FATAL(text) _log(__FILE__, __LINE__, ae::TRC_LEVEL_FATAL, text)
#define TRC_ERROR(text) _log(__FILE__, __LINE__, ae::TRC_LEVEL_ERROR, text)
#define TRC_WARN(text) _log(__FILE__, __LINE__, ae::TRC_LEVEL_WARN, text)
#define TRC_INFO(text) _log(__FILE__, __LINE__, ae::TRC_LEVEL_INFO, text)
#define TRC_DEBUG(text) _log(__FILE__, __LINE__, ae::TRC_LEVEL_DEBUG, text)
#define TRC_TRACE(text) _log(__FILE__, __LINE__, ae::TRC_LEVEL_TRACE, text)
#define TRC_SCOPED(text) ae::ScopedLogLogger _scope(*this, text)
#define TRC_SCOPED_FUNC() ae::ScopedLogLogger _scope(*this, __PRETTY_FUNCTION__)

// Outside of LogSource class these macros can be used but a pointer to a
// Logger needs to be provided manually
#define TRC_LOGGER_FATAL(logger, text)                                         \
    logger->log(__FILE__, __LINE__, ae::TRC_LEVEL_FATAL, text)
#define TRC_LOGGER_ERROR(logger, text)                                         \
    logger->log(__FILE__, __LINE__, ae::TRC_LEVEL_ERROR, text)
#define TRC_LOGGER_WARN(logger, text)                                          \
    logger->log(__FILE__, __LINE__, ae::TRC_LEVEL_WARN, text)
#define TRC_LOGGER_INFO(logger, text)                                          \
    logger->log(__FILE__, __LINE__, ae::TRC_LEVEL_INFO, text)
#define TRC_LOGGER_DEBUG(logger, text)                                         \
    logger->log(__FILE__, __LINE__, ae::TRC_LEVEL_DEBUG, text)
#define TRC_LOGGER_TRACE(logger, text)                                         \
    logger->log(__FILE__, __LINE__, ae::TRC_LEVEL_TRACE, text)
#define TRC_LOGGER_SCOPED(logger, text) ae::ScopedLogLogger _scope(logger, text)
#define TRC_LOGGER_SCOPED_FUNC(logger)                                         \
    ae::ScopedLogLogger _scope(logger, __PRETTY_FUNCTION__)

namespace ae {
class LogSource {
  public:
    LogSource(std::string name)
      : _logger(LogManager::instance().getLogger(name)) {}

    void _log(std::string filename, uint32_t line, uint8_t level,
              std::string trace) const {
        _logger->log(filename, line, level, trace);
    }

    void _log(uint8_t level, std::string trace) const {
        _logger->log(level, trace);
    }

    const std::shared_ptr<Logger>& _getLogger() const { return _logger; }

  private:
    std::shared_ptr<Logger> _logger;
};

class ScopedLogLogger {
  public:
    ScopedLogLogger(const LogSource& src, std::string text)
      : _logger(src._getLogger()), _text(text) {
        entryTrace();
        //++_instances;
    }
    ScopedLogLogger(std::shared_ptr<Logger> logger, std::string text)
      : _logger(logger), _text(text) {
        entryTrace();
        //++_instances;
    }

    ~ScopedLogLogger() {
        //--_instances;
        exitTrace();
    }

  private:
    void entryTrace() {
        _logger->log(
          TRC_LEVEL_TRACE,
          /*std::string(_instances * 2, ' ') + */ std::string("--> ") + _text);
    }
    void exitTrace() {
        _logger->log(
          TRC_LEVEL_TRACE,
          /*std::string(_instances * 2, ' ') + */ std::string("<-- ") + _text);
    }
    const std::shared_ptr<Logger> _logger;
    std::string _text;
    // static int32_t _instances;
};
}
