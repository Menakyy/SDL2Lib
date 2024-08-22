#include "Logger.h"

#define LOG true
#define LOG_FILE false

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message)
{
    if (LOG)
    {
        std::cout << message << std::endl;
    }

    if (logFile.is_open() && LOG_FILE)
    {
        logFile << message << std::endl;
    }
}

void Logger::logToFile(const std::string& filePath)
{
    if (logFile.is_open())
    {
        logFile.close();
    }
    logFile.open(filePath, std::ios::out | std::ios::app);
    if (!logFile.is_open())
    {
        std::cerr << "Failed to open log file: " << filePath << std::endl;
    }
}

void Logger::stopLoggingToFile()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}
