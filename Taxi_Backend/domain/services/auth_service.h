#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "../domain.h"
#include "../../adapters/session.h"
#include "../../infrastructure/repository/user_repository/user_repository.h"
#include "../../infrastructure/security/hash_util.h"

class AuthService {
private:
    SQLiteUserRepository& userRepo;
public:
    AuthService(SQLiteUserRepository& repo) : userRepo(repo) {}

    bool registerUser(const string& username, int age, const string& email, const string& password, const string& role) {
        if (userRepo.userExists(username)) {
            cout << "User already exists!" << endl;
            return false;
        }

        string hashedPassword = HashUtil::hashPassword(password);
        User* newUser = nullptr;

        if (role == "Passenger") {
            newUser = new Passenger(nullptr, username, age, email, hashedPassword, 0, role);
        }
        else if (role == "Driver") {
            newUser = new Driver(nullptr, username, age, email, hashedPassword, 0, role);
        }
        else {
            cout << "Invalid role specified!" << endl;
            return false;
        }

        userRepo.createUser(*newUser);

        delete newUser;
        return true;
    }

    bool loginUser(const string& email, const string& password) {
        session->resetSession();
        User* user = userRepo.findUserByEmail(email);
        if (user == nullptr) {
            cout << "User not found!" << endl;
            return false;
        }

        if (HashUtil::verifyPassword(password, user->getPassword())) {
            string role = userRepo.findUserRoleByEmail(email);

            cout << endl;
            if (role == "Passenger") {
                ;
                // cout << "Welcome, Passenger " << user->getName() << "!" << endl;
            }
            else if (role == "Driver") {
                ;
                // __asm {nop};
                // cout << "Welcome, Driver " << user->getName() << "!" << endl;
            }
            else {
                ;
                // cout << "Welcome, " << user->getName() << "!" << endl;
            }

            Session::getInstance()->setUser(user->getUserId() ? *user->getUserId() : -1, user->getEmail(), role);
            delete user;
            return true;
        }
        else {
            cout << "DEV MODE: Invalid password!" << endl;
            delete user;
            return false;
        }
    }
};

#endif // AUTH_SERVICE_H
