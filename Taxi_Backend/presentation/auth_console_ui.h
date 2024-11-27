#ifndef AUTH_CONSOLE_UI_H
#define AUTH_CONSOLE_UI_H

#include "../domain/use_cases/auth_service.h"
#include "../infrastructure/db_provider.h"
#include "../application/interfaces/i_auth_console.h"

#include "console_ui.h"

struct UserInfo {
    string username;
    string email;
    string password;
    string role;
    int age;
};

class AuthConsole : public IAuthConsole {
private:
    AuthUseCase authUseCase;
    DatabaseProvider& dbProvider;

public:
    AuthConsole(DatabaseProvider& dbProvider)
        : dbProvider(dbProvider), authUseCase(dbProvider.setUserRepositoryForConsole()) {}

    void display_welcome_message() {
        std::cout << "===================================" << std::endl;
        std::cout << "||           Welcome             ||" << std::endl;
        std::cout << "||      To Our Application       ||" << std::endl;
        std::cout << "===================================" << std::endl;
    }

    void displayTerminal() {
        display_welcome_message();

        while (true) {
            std::cout << "====================================" << std::endl;
            std::cout << "||         Authentication         ||" << std::endl;
            std::cout << "====================================" << std::endl;
            std::cout << "|| 1. Login                       ||" << std::endl;
            std::cout << "|| 2. Register                    ||" << std::endl;
            std::cout << "|| 3. Quit                        ||" << std::endl;
            std::cout << "====================================" << std::endl;
            std::cout << "|| Your option: ";

            int choice;
            cin >> choice;
            cout << endl;

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
