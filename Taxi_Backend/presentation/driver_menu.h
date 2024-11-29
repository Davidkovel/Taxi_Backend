#ifndef DRIVER_MENU_H
#define DRIVER_MENU_H

#include "../application/interfaces/i_menu.h"

class DriverMenu : public IMenu<DriverDTO> {
public:
    void displayMenu(DriverDTO& dto) override {
        while (true) {
            cout << "========================================" << endl;
            cout << "||          Driver Menu               ||" << endl;
            cout << "========================================" << endl;
            cout << "|| 1. Withdraw balance                ||" << endl;
            cout << "|| 2. Statistic                       ||" << endl;
            cout << "|| 2. Show your result orders (.csv)  ||" << endl;
            cout << "|| 3. Logout                          ||" << endl;
            cout << "========================================" << endl;
            cout << "|| Your option: ";

            int choice;
            cin >> choice;

            if (choice == 3) {
                cout << "Exiting to the login menu..." << endl;
                break;
            }

            dto.call_function(choice);
        }
    }
};


#endif // !DRIVER_MENU_H