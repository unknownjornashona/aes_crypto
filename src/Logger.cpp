#include "Logger.h"
#include <fstream>

void Logger::log(const std::string &message) {
    std::ofstream logFile("crypto_manager.log", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    }
}
