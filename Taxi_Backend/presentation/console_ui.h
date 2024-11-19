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

    void display_terminal() override {
        cout << "Choose an option:" << endl;
        cout << "1. Book a taxi" << endl;
        cout << "2. Show your booking orders (.csv format)" << endl;
        cout << "Your option: ";

        int choice;
        cin >> choice;

        dto.call_function(choice);
    }
};

#endif // CONSOLE_UI_H
