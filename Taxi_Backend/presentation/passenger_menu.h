#ifndef PASSENGER_MENU_H
#define PASSENGER_MENU_H

#include "../application/interfaces/i_menu.h"

class PassengerMenu : public IMenu<PassengerDTO> {
public:
    void displayMenu(PassengerDTO& dto) override {
        while (true) {
            cout << "========================================" << endl;
            cout << "||         Passenger Menu             ||" << endl;
            cout << "========================================" << endl;
            cout << "|| 1. Book a taxi                     ||" << endl;
            cout << "|| 2. Deposit balance                 ||" << endl;
            cout << "|| 3. Show your booking orders (.csv) ||" << endl;
            cout << "|| 4. Logout                          ||" << endl;
            cout << "========================================" << endl;
            cout << "|| Your option: ";

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

#endif // !PASSENGER_MENU_H