#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "../application/interfaces/i_console_ui.h"
#include "../domain/use_cases/dto.h"
#include "../infrastructure/db_provider.h"

class CONSOLE_UI : virtual public IConsole {
private:
    DTO dto;
public:
    CONSOLE_UI() = default;

    CONSOLE_UI(DatabaseProvider* provider) : dto(provider) {}

    void display_main_menu() override {
        while (true) {
            std::cout << "========================================" << std::endl;
            std::cout << "||           Choose an option:        ||" << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "|| 1. Book a taxi                     ||" << std::endl;
            std::cout << "|| 2. Deposit balance                 ||" << std::endl;
            std::cout << "|| 3. Show your booking orders (.csv) ||" << std::endl;
            std::cout << "|| 4. Logout                          ||" << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "|| Your option: ";

            int choice;
            cin >> choice;

            cout << endl;

            if (choice == 4) {
                cout << "Exiting to the login menu..." << endl;
                break;
            }

            dto.call_function(choice);
        }
    }

};

#endif // CONSOLE_UI_H
