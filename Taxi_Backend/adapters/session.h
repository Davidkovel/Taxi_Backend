#ifndef SESSION_H
#define SESSION_H

#include "../lib/lib.h"

// Pattern Singleton

class Session {
private:
    static Session* instance;
    int user_id;
    string email;
    string role;

    Session() : user_id(-1), email("Null"), role("Null") {}

public:
    static Session* getInstance() {
        if (!instance) {
            instance = new Session();
        }
        return instance;
    }

    void setUser(int id, const string& user_email, const string& user_role) {
        this->user_id = id;
        this->email = user_email;
        this->role = user_role;
    }

    
    int getUserId() const { return user_id; }
    string getUserEmail() const { return email; }
    string getUserRole() const { return role; }

    void resetSession() {
        user_id = -1;
        email = "Null";
        role = "Null";
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
