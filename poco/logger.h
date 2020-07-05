#pragma once
#include <iostream>

#include "Poco/ConsoleChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"

namespace base
{
const uint8_t TRC_LEVEL_FATAL = 1;
const uint8_t TRC_LEVEL_ERROR = 3;
const uint8_t TRC_LEVEL_WARN = 4;
const uint8_t TRC_LEVEL_INFO = 6;
const uint8_t TRC_LEVEL_DEBUG = 7;
const uint8_t TRC_LEVEL_TRACE = 8;

class MyColorConsoleChannel : public Poco::ColorConsoleChannel
{
   public:
    MyColorConsoleChannel(std::ostream& _stream) : Poco::ColorConsoleChannel(_stream) {}
    ~MyColorConsoleChannel() {}
};

class MyFormattingChannel : public Poco::FormattingChannel
{
   public:
    MyFormattingChannel(Poco::Formatter* pFormatter, Poco::Channel* pChannel)
        : Poco::FormattingChannel(pFormatter, pChannel)
    {
    }
    ~MyFormattingChannel() {}
};

class Logger
{
   public:
    Logger(std::string name)
        : _name(name), _logger(Poco::Logger::get(name)), pCons(), pPF(), pFC()
    {
        pCons.reset(new MyColorConsoleChannel(std::cout));
        pPF.reset(new Poco::PatternFormatter);
        pPF->setProperty("pattern", "[%E.%F] [%q] [%P.%I] [%s] %t | %U:%u");
        pFC.reset(new MyFormattingChannel(pPF.get(), pCons.get()));

        _logger.setLevel(Poco::Message::PRIO_ERROR);
        _logger.setChannel(pFC.get());
    }

    ~Logger() {}

    Poco::Message::Priority lvl2native(uint8_t lvl)
    {
        return static_cast<Poco::Message::Priority>(lvl);
    }

    void setLogLevel(uint8_t level) { _logger.setLevel(lvl2native(level)); }

    void log(std::string filename, uint32_t line, uint8_t level, std::string trace)
    {
        _logger.log(
            Poco::Message(_name, trace, lvl2native(level), filename.c_str(), line));
    }

    void log(uint8_t level, std::string trace)
    {
        _logger.log(Poco::Message(_name, trace, lvl2native(level)));
    }

    void fatal(std::string trace) { _logger.fatal(trace); }

    void error(std::string trace) { _logger.error(trace); }

    void warn(std::string trace) { _logger.warning(trace); }

    void info(std::string trace) { _logger.information(trace); }

    void debug(std::string trace) { _logger.debug(trace); }

    void trace(std::string trace) { _logger.trace(trace); }

   private:
    std::string _name;
    Poco::Logger& _logger;
    std::unique_ptr<MyColorConsoleChannel> pCons;
    std::unique_ptr<Poco::PatternFormatter> pPF;
    std::unique_ptr<MyFormattingChannel> pFC;
};
}  // namespace base
