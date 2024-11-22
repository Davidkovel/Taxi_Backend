#ifndef AUTH_USE_CASE_H
#define AUTH_USE_CASE_H

#include "../domain/domain.h"
#include "../infrastructure/repository/user_repository/user_repository.h"
#include "../infrastructure/security/hash_util.h"

class AuthUseCase {
private:
    SQLiteUserRepository& userRepo;
public:
    AuthUseCase(SQLiteUserRepository& repo) : userRepo(repo) {}

    bool registerUser(const string& username, int age, const string& email, const string& password, const string& role) {
        if (userRepo.userExists(username)) {
            cout << "User already exists!" << endl;
            return false;
        }

        string hashedPassword = HashUtil::hashPassword(password);
        User* newUser = nullptr;

        if (role == "Passenger") {
            newUser = new Passenger(username, age, email, hashedPassword, role);
        }
        else if (role == "Driver") {
            newUser = new Driver(username, age, email, hashedPassword, role);
        }
        else {
            cout << "Invalid role specified!" << endl;
            return false;
        }

        userRepo.createUser(*newUser);
        delete newUser;
        return true;
    }

    bool loginUser(const string& username, const string& password) {
        User* user = userRepo.findUserByEmail(username);
        if (user == nullptr) {
            cout << "User not found!" << endl;
            return false;
        }

        if (HashUtil::verifyPassword(password, user->getPassword())) {
            cout << "Welcome, " << user->getName() << "!" << endl;
            return true;
        }
        else {
            cout << "Invalid password!" << endl;
            return false;
        }
    }
};

#endif // AUTH_USE_CASE_H
