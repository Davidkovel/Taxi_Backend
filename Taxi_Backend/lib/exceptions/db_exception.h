#ifndef DB_EXCEPTION_H

#define DB_EXCEPTION_H
#define _CRT_SECURE_NO_WARNINGS

#include "../lib.h"

namespace exceptions {

    class DBProcessResult abstract {
    public:
        virtual void get_message() = 0;
    };

    class DBException : public DBProcessResult {
    private:
        string message;
    public:
        DBException() = default;
        DBException(const string& message) {
            this->message = message;
        }

        void get_message() override {
            cout << message.c_str() << endl;
        }
    };

}

#endif // !DB_EXCEPTION_H