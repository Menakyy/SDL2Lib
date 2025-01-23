#include "Logger.h"

Logger::LogLevel Logger::globalLogLevel = Logger::LogLevel::none;
std::ofstream    Logger::logFile;
std::string      Logger::logFileName;

void Logger::initialize(const std::string& logFileName, LogLevel logLevel)
{
    Logger::logFileName    = logFileName;
    Logger::globalLogLevel = logLevel;

    Logger::logFile.open(Logger::logFileName, std::ios::out | std::ios::app);
    if (!Logger::logFile.is_open())
    {
        std::cerr << "Could not open log file: " << Logger::logFileName << std::endl;
    }
}

void Logger::shutdown()
{
    if (Logger::logFile.is_open())
    {
        Logger::logFile.close();
    }
}

void Logger::info(const char* format, ...)
{
    if (globalLogLevel > LogLevel::info)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    log(LogLevel::info, format, args);
    va_end(args);
}

void Logger::warning(const char* format, ...)
{
    if (globalLogLevel > LogLevel::warning)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    log(LogLevel::warning, format, args);
    va_end(args);
}

void Logger::error(const char* format, ...)
{
    if (globalLogLevel > LogLevel::error)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    log(LogLevel::error, format, args);
    va_end(args);
}

void Logger::fatal(const char* format, ...)
{
    if (globalLogLevel > LogLevel::fatalError)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    log(LogLevel::fatalError, format, args);
    va_end(args);
    std::abort();
}

void Logger::debug(const char* format, ...)
{
    if (globalLogLevel > LogLevel::debug)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    log(LogLevel::debug, format, args);
    va_end(args);
}

Logger::LogLevel Logger::getLoggerLevel()
{
    return globalLogLevel;
}

void Logger::log(const LogLevel logLevel, const char* format, va_list args)
{
    if (logLevel < globalLogLevel)
    {
        return;
    }

    std::time_t currentTime = std::time(nullptr);
    std::string timestamp   = getFormattedTimestamp(currentTime);

    char buffer[MAX_BUFFER_LENGTH];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Zapisz log do pliku
    if (logFile.is_open())
    {
        logFile << "[" << getLevelName(logLevel) << "] " << timestamp << ": " << buffer << std::endl;
    }

    // Wyświetl log na konsoli
    std::cout << "[" << getLevelName(logLevel) << "] " << timestamp << ": " << buffer << std::endl;
}

std::string Logger::getLevelName(LogLevel logLevel)
{
    switch (logLevel)
    {
        case LogLevel::none:
            return "NONE";
        case LogLevel::fatalError:
            return "FATAL ERROR";
        case LogLevel::error:
            return "ERROR";
        case LogLevel::warning:
            return "WARNING";
        case LogLevel::info:
            return "INFO";
        case LogLevel::debug:
            return "DEBUG";
    }
    return "LOG";
}

std::string Logger::getFormattedTimestamp(std::time_t currentTime)
{
    std::tm*           localTime = std::localtime(&currentTime);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}