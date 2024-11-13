#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"

class Driver : public User {
private:
    bool busy;
    string password;

public:
    Driver(const string& name, int age, const string& email, const string& password, bool busy = false)
        : User(name, age, email), password(password), busy(busy) {}

    string getRole() const override {
        return "Driver";
    }

    bool authenticate(const string& inputPassword) override {
        return password == inputPassword;
    }

    bool isBusy() const {
        return busy;
    }

    void setBusy(bool status) {
        busy = status;
    }
};

#endif // DRIVER_H
