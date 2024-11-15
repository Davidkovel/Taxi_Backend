#ifndef PASSENGER_H
#define PASSENGER_H

#include "user.h"


class User abstract {
public:
    string name;
    int age;
    string email;

    User(string name, int age, string email) : name(name), age(age), email(email) {}

    virtual string getRole() const = 0;
    virtual bool authenticate(const string& password) = 0;
    virtual ~User() = default;
};


class Passenger : public User {
private:
    string password;

public:
    Passenger(const string& name, int age, const string& email, const string& password) : User(name, age, email) {
        this->password = password;
    }

    string getRole() const override {
        return "Passenger";
    }

    bool authenticate(const string& inputPassword) override {
        return password == inputPassword;
    }
};

#endif // PASSENGER_H
