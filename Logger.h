#ifndef LOGGER
#define LOGGER

#include <fstream>
#include <iostream>
#include <string>

class Logger
{
public:
    static Logger& getInstance();

    void log(const std::string& message);
    void logToFile(const std::string& filePath);
    void stopLoggingToFile();

private:
    Logger() = default;
    ~Logger();

    std::ofstream logFile;
};


#endif /* LOGGER */
