#ifndef LOGGER_H
#define LOGGER_H

#include "lib.h"

namespace logger {

    enum class LogLevel {
        INFO,
        DEBUG,
        ERRO,
        WARNING,
    };

    string getCurrentTimestamp() {
        auto now = chrono::system_clock::now();
        auto in_time_t = chrono::system_clock::to_time_t(now);

        tm tm{};
        gmtime_s(&tm, &in_time_t);

        stringstream ss;
        ss << put_time(&tm, "%H:%M:%S");
        return ss.str();
    }

    class Logger {
    private:
        ofstream logFile;
        mutex mtx;
        LogLevel logLevel;
        bool loggingEnabled;

        map<LogLevel, string> levelToString{
            {LogLevel::INFO, "INFO"},
            {LogLevel::DEBUG, "DEBUG"},
            {LogLevel::ERRO, "ERROR"},
            {LogLevel::WARNING, "WARNING"},
        };

        map<LogLevel, string> levelToColor{
            {LogLevel::INFO, "\033[1;32m"},
            {LogLevel::DEBUG, "\033[1;34m"},
            {LogLevel::ERRO, "\033[1;31m"},
            {LogLevel::WARNING, "\033[1;33m"},
        };

        string resetColor = "\033[0m";

        Logger(const string& filePath = "default.log", LogLevel level = LogLevel::INFO, bool enableLogging = true)
            : logLevel(level), loggingEnabled(enableLogging) {
            logFile.open(filePath, ios::app);
            if (!logFile.is_open()) {
                throw runtime_error("Failed to open or create log file: " + filePath);
            }
        }

        ~Logger() {
            if (logFile.is_open()) {
                logFile.close();
            }
        }

    public:
        Logger(const Logger&) = delete;            // ”бираем возможность копировани€
        Logger& operator=(const Logger&) = delete; // ”бираем возможность присваивани€

        static Logger& getInstance(const string& filePath = "default.log", LogLevel level = LogLevel::INFO, bool enableLogging = true) {
            static Logger instance(filePath, level, enableLogging);
            return instance;
        }

        void setLoggingEnabled(bool enabled) {
            loggingEnabled = enabled;
        }

        void log(LogLevel level, const string& message) {
            if (!loggingEnabled) return;

            lock_guard<mutex> lock(mtx);
            if (level >= logLevel) {
                string logMessage = "[" + getCurrentTimestamp() + "] [" + levelToString[level] + "] " + message;
                string colorMessage = levelToColor[level] + logMessage + resetColor;
                cout << colorMessage << endl;
                if (logFile.is_open()) {
                    logFile << logMessage << endl;
                }
            }
        }

        void info(const string& message) {
            log(LogLevel::INFO, message);
        }

        void debug(const string& message) {
            log(LogLevel::DEBUG, message);
        }

        void error(const string& message) {
            log(LogLevel::ERRO, message);
        }

        void warning(const string& message) {
            log(LogLevel::WARNING, message);
        }
    };

}

#endif // LOGGER_H



// mutex (мьютекс) используетс€ дл€ обеспечени€ потокобезопасности