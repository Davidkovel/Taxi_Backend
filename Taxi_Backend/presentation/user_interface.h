#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

// #include "../use_cases/obs.h"

class IUser {
public:

    virtual void display_terminal() = 0;
    virtual void registerUser(User* user) = 0;
    virtual User* login(const string& email, const string& password) = 0;
};

#endif // USER_INTERFACE_H