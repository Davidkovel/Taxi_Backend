#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "../presentation/user_interface.h"
#include "../use_cases/dto.h"
#include "../infrastructure/db_provider.h"

class CONSOLE_UI : virtual public IUser {
private:
    DTO dto;
public:
    CONSOLE_UI() = default;

    CONSOLE_UI(DatabaseProvider* provider) : dto(provider) {}

    void display_main_menu() override {
        while (true) {
            cout << "Choose an option:" << endl;
            cout << "1. Book a taxi" << endl;
            cout << "2. Deposit balance" << endl;
            cout << "3. Show your booking orders (.csv format)" << endl;
            cout << "4. Quit" << endl;
            cout << "Your option: ";

            int choice;
            cin >> choice;

            if (choice == 4) {
                cout << "Exiting to the login menu..." << endl;
                break;
            }

            dto.call_function(choice);
        }
    }

};

#endif // CONSOLE_UI_H
