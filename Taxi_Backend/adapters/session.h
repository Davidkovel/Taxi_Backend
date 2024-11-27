#ifndef SESSION_H
#define SESSION_H

#include "../lib/lib.h"

// Pattern Singleton

class Session {
private:
    static Session* instance;
    int user_id;
    string email;

    Session() : user_id(-1), email("Null") {}

public:
    static Session* getInstance() {
        if (!instance) {
            instance = new Session();
        }
        return instance;
    }

    void setUser(int id, const string& user_email) {
        user_id = id;
        email = user_email;
    }

    int getUserId() const { return user_id; }
    string getUserEmail() const { return email; }

    void resetSession() {
        user_id = -1;
        email = "";
    }

    bool isUserLoggedIn() const {
        return user_id != -1;
    }

    ~Session () {}
};

// Инициализация статического члена
Session* Session::instance = nullptr;
Session* session = Session::getInstance();


#endif // SESSION_H
