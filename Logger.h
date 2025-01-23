#ifndef LOGGER
#define LOGGER

#include <cstdarg>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

class Logger
{
public:
    static constexpr uint16_t MAX_BUFFER_LENGTH = 256;

    enum class LogLevel
    {
        none,
        debug,
        info,
        warning,
        error,
        fatalError,
    };

    static void initialize(const std::string& logFileName, LogLevel logLevel = LogLevel::error);
    static void shutdown();

    static void     info(const char* format, ...);
    static void     warning(const char* format, ...);
    static void     error(const char* format, ...);
    static void     fatal(const char* format, ...);
    static void     debug(const char* format, ...);
    static LogLevel getLoggerLevel();

private:
    static LogLevel      globalLogLevel;
    static std::ofstream logFile;
    static std::string   logFileName;

    static std::string getLevelName(LogLevel logLevel);
    static void        log(const LogLevel logLevel, const char* format, va_list args);
    static std::string getFormattedTimestamp(std::time_t currentTime);
};

#endif /* LOGGER */
