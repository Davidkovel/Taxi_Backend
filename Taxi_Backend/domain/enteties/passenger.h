#ifndef PASSENGER_H
#define PASSENGER_H

#include "user.h"

class User abstract {
public:
    string name;
    int age;
    string email;
    string passwordHash;
    double balance;
    string role;

    User(string name, int age, string email, const string& passHash, double balance, const string& role) : name(name), age(age), email(email), passwordHash(passHash), balance(balance), role(role) {}

    string getName() const { return name; }
    int getAge() const { return age; }
    string getEmail() const { return email; }
    string getPassword() const { return passwordHash; }
    double getBalance() const { return balance; }

    void setBalance(double balance)
    {
        this->balance = balance;
    }

    virtual string getRole() const = 0;
    virtual ~User() = default;

};


class Passenger : public User {
public:
    Passenger(const string& name, int age, const string& email, const string& password, double balance, const string& role) : User(name, age, email, password, balance, role) {}

    string getRole() const override {
        return "Passenger";
    }
};



class Driver : public User {
private:
    bool busy;
public:
    Driver(const string& name, int age, const string& email, const string& password, double balance, const string& role, bool busy = false)
        : User(name, age, email, password, balance, role), busy(busy) {}

    string getRole() const override {
        return "Driver";
    }

    bool isBusy() const {
        return busy;
    }

    void setBusy(bool status) {
        busy = status;
    }

};

#endif // PASSENGER_H
