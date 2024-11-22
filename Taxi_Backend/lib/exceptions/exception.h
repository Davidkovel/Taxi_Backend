#ifndef EXCEPTION_H

#define EXCEPTION_H
#define _CRT_SECURE_NO_WARNINGS

#include "../lib.h"

namespace exceptions {

    class BaseException : public std::exception {
    protected:
        string message;
        string cause;
    public:
        BaseException() = default;

        explicit BaseException(const string& message, const string& cause = "")
            : message(message), cause(cause) {}

        virtual const char* what() const noexcept override {
            if (!cause.empty()) {
                return (message + " | Caused by: " + cause).c_str();
            }
            return message.c_str();
        }

        virtual void log() const {
            cerr << "[ERROR] " << what() << endl;
        }
    };

    class DBException : public BaseException {
    public:
        DBException() = default;

        explicit DBException(const string& message, const string& cause = "")
            : BaseException(message, cause) {}

        void log() const override {
            cerr << "[DB ERROR] " << what() << endl;
        }
    };

    class CSVFileException : public BaseException {
    public:
        CSVFileException() = default;

        explicit CSVFileException(const string& message, const string& cause = "")
            : BaseException(message, cause) {}

        void log() const override {
            cerr << "[CSV ERROR] " << what() << endl;
        }
    };

    class ProcessException : public BaseException {
    public:
        ProcessException() = default;

        explicit ProcessException(const string& message, const string& cause = "")
            : BaseException(message, cause) {}

        void log() const override {
            cerr << "[PROCESS ERROR] " << what() << endl;
        }
    };

}

#endif // !EXCEPTION_H