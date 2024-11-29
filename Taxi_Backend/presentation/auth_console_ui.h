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
        cout << "===================================" << endl;
        cout << "||           Welcome             ||" << endl;
        cout << "||      To Our Application       ||" << endl;
        cout << "===================================" << endl;
    }

    void displayTerminal() {
        display_welcome_message();

        while (true) {
            cout << "====================================" << endl;
            cout << "||         Authentication         ||" << endl;
            cout << "====================================" << endl;
            cout << "|| 1. Login                       ||" << endl;
            cout << "|| 2. Register                    ||" << endl;
            cout << "|| 3. Quit                        ||" << endl;
            cout << "====================================" << endl;
            cout << "|| Your option: ";

            int choice;
            cin >> choice;
            cout << endl;

            if (choice == 3) break;

            if (choice == 1) { // Login
                UserInfo user = setInformationLogin();
                if (authUseCase.loginUser(user.email, user.password)) {
                    system("cls");
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
                    system("cls");
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
        cout << "Enter your role (Passenger or Driver): ";
        cin >> user.role;

        return user;
    }
};


#endif // AUTH_CONSOLE_UI_H
