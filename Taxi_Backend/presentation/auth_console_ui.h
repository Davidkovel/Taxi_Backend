#ifndef AUTH_CONSOLE_UI_H
#define AUTH_CONSOLE_UI_H

#include "../domain/services/auth_service.h"
#include "../infrastructure/db_provider.h"
#include "../application/interfaces/i_auth_console.h"

#include "console_ui.h"
#include "console_utils.h"

struct UserInfo {
    string username;
    string email;
    string password;
    string role;
    int age;
};

class AuthConsole : public IAuthConsole {
private:
    AuthService authUseCase;
    DatabaseProvider& dbProvider;

public:
    AuthConsole(DatabaseProvider& dbProvider)
        : dbProvider(dbProvider), authUseCase(dbProvider.setUserRepositoryForConsole()) {}

    void display_welcome_message() {
        ConsoleUtils::setColor(ConsoleUtils::GREEN);
        ConsoleUtils::printAnimated("===================================", 10);
        ConsoleUtils::printAnimated("||           Welcome             ||", 10);
        ConsoleUtils::printAnimated("||      To Our Application       ||", 10);
        ConsoleUtils::printAnimated("===================================", 10);
        ConsoleUtils::resetColor();
    }

    void displayTerminal() {
        display_welcome_message();

        while (true) {
            ConsoleUtils::setColor(ConsoleUtils::BLUE);
            cout << "====================================" << endl;
            cout << "||         Authentication         ||" << endl;
            cout << "====================================" << endl;
            cout << "|| 1. Login                       ||" << endl;
            cout << "|| 2. Register                    ||" << endl;
            cout << "|| 3. Quit                        ||" << endl;
            cout << "====================================" << endl;
            cout << "|| Your option: ";
            ConsoleUtils::resetColor();

            int choice;
            cin >> choice;
            cout << endl;

            if (choice == 3) {
                ConsoleUtils::setColor(ConsoleUtils::RED);
                ConsoleUtils::printAnimated("Exiting the application. Goodbye!", 50);
                ConsoleUtils::resetColor();
                break;
            }

            if (choice == 1) { // Login
                UserInfo user = setInformationLogin();
                if (authUseCase.loginUser(user.email, user.password)) {
                    ConsoleUtils::setColor(ConsoleUtils::GREEN);
                    ConsoleUtils::printAnimated("Login details recorded successfully.", 50);
                    system("cls");
                    ConsoleUtils::printAnimated("Login successful!", 50);
                    ConsoleUtils::resetColor();

                    CONSOLE_UI consoleUi(&dbProvider);
                    consoleUi.display_main_menu();
                }
                else {
                    ConsoleUtils::setColor(ConsoleUtils::RED);
                    ConsoleUtils::printAnimated("Invalid username or password!", 50);
                    ConsoleUtils::resetColor();
                }
            }
            else if (choice == 2) { // Register
                UserInfo user = setInformationRegister();
                if (authUseCase.registerUser(user.username, user.age, user.email, user.password, user.role)) {
                    ConsoleUtils::setColor(ConsoleUtils::GREEN);
                    ConsoleUtils::printAnimated("Registration details recorded successfully!", 50);
                    system("cls");
                    ConsoleUtils::printAnimated("Registration successful!", 50);
                    ConsoleUtils::resetColor();
                }
                else {
                    ConsoleUtils::setColor(ConsoleUtils::RED);
                    ConsoleUtils::printAnimated("Failed to register user!", 50);
                    ConsoleUtils::resetColor();
                }
            }
            else {
                ConsoleUtils::setColor(ConsoleUtils::RED);
                ConsoleUtils::printAnimated("Invalid option. Please try again.", 50);
                ConsoleUtils::resetColor();
            }
        }
    }

    UserInfo setInformationLogin() {
        UserInfo user;

        ConsoleUtils::setColor(ConsoleUtils::CYAN);
        ConsoleUtils::printAnimated("Please enter your login details below:", 50);
        ConsoleUtils::resetColor();

        ConsoleUtils::setColor(ConsoleUtils::YELLOW);
        cout << "Enter email: ";
        ConsoleUtils::resetColor();
        cin >> user.email;

        ConsoleUtils::setColor(ConsoleUtils::YELLOW);
        cout << "Enter password: ";
        ConsoleUtils::resetColor();
        cin >> user.password;

        ConsoleUtils::setColor(ConsoleUtils::GREEN);
        ConsoleUtils::resetColor();

        return user;
    }

    UserInfo setInformationRegister() {
        UserInfo user;

        ConsoleUtils::setColor(ConsoleUtils::CYAN);
        ConsoleUtils::printAnimated("Welcome to the registration process!", 50);
        ConsoleUtils::printAnimated("Please fill in the following details:", 50);
        ConsoleUtils::resetColor();

        ConsoleUtils::setColor(ConsoleUtils::YELLOW);
        cout << "Enter username: ";
        ConsoleUtils::resetColor();
        cin >> user.username;

        ConsoleUtils::setColor(ConsoleUtils::YELLOW);
        cout << "Enter age: ";

        while (!(cin >> user.age) || user.age <= 0) {
            ConsoleUtils::setColor(ConsoleUtils::RED);
            cout << "Invalid age. Please enter a valid age: ";
            ConsoleUtils::resetColor();
            cin.clear();
            cin.ignore('\n');
        }

        cout << "Enter email: ";
        while (true) {
            ConsoleUtils::setColor(ConsoleUtils::YELLOW);
            ConsoleUtils::resetColor();
            cin >> user.email;

            if (user.email.find('@') != string::npos && user.email.find('.') != string::npos) {
                break;
            }

            ConsoleUtils::setColor(ConsoleUtils::RED);
            cout << "Invalid email. Please try again: ";
            ConsoleUtils::resetColor();
        }

        ConsoleUtils::setColor(ConsoleUtils::YELLOW);
        cout << "Enter password: ";
        ConsoleUtils::resetColor();
        cin >> user.password;

        ConsoleUtils::setColor(ConsoleUtils::YELLOW);
        cout << "Enter your role (Passenger or Driver): ";
        ConsoleUtils::resetColor();
        while (true) {
            cin >> user.role;
            if (user.role == "Passenger" || user.role == "Driver") {
                break;
            }
            ConsoleUtils::setColor(ConsoleUtils::RED);
            cout << "Invalid role. Please enter either 'Passenger' or 'Driver': ";
            ConsoleUtils::resetColor();
        }

        ConsoleUtils::setColor(ConsoleUtils::GREEN);
        ConsoleUtils::resetColor();

        return user;
    }
};


#endif // AUTH_CONSOLE_UI_H
