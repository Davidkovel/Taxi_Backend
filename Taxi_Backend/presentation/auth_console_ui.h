#ifndef AUTH_CONSOLE_UI_H
#define AUTH_CONSOLE_UI_H

#include "../use_cases/auth.h"
#include "../infrastructure/db_provider.h"
#include "console_ui.h"

struct UserInfo {
    string username;
    string email;
    string password;
    string role;
    int age;
};

class AuthConsole {
private:
    AuthUseCase authUseCase;
    DatabaseProvider& dbProvider;

public:
    AuthConsole(DatabaseProvider& dbProvider)
        : dbProvider(dbProvider), authUseCase(dbProvider.setUserRepositoryForConsole()) {}

    void displayTerminal() {
        while (true) {
            cout << "Choose an option:" << endl;
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Quit" << endl;
            cout << "Your option: ";

            int choice;
            cin >> choice;

            if (choice == 3) break;

            if (choice == 1) { // Login
                UserInfo user = setInformationLogin();
                if (authUseCase.loginUser(user.email, user.password)) {
                    cout << "Login successful!" << endl;

                    CONSOLE_UI consoleUi(&dbProvider);
                    consoleUi.display_main_menu();
                }
                else {
                    cout << "Invalid username or password!" << endl;
                }
            }
            else if (choice == 2) { // Register
                UserInfo user = setInformationRegister();
                if (authUseCase.registerUser(user.username, user.age, user.email, user.password, user.role)) {
                    cout << "Registration successful!" << endl;
                }
                else {
                    cout << "Failed to register user!" << endl;
                }
            }
        }
    }

    UserInfo setInformationLogin() {
        UserInfo user;
        cout << "Enter email: ";
        cin >> user.email;
        cout << "Enter password: ";
        cin >> user.password;

        return user;
    }

    UserInfo setInformationRegister() {
        UserInfo user;
        cout << "Enter username: ";
        cin >> user.username;
        cout << "Enter age: ";
        cin >> user.age;
        cout << "Enter email: ";
        cin >> user.email;
        cout << "Enter password: ";
        cin >> user.password;
        cout << "Enter your role: ";
        cin >> user.role;

        return user;
    }
};


#endif // AUTH_CONSOLE_UI_H
