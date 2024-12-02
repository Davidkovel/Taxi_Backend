#ifndef DRIVER_MENU_H
#define DRIVER_MENU_H

#include "../application/interfaces/i_menu.h"
#include "console_utils.h"

class DriverMenu : public IMenu<DriverDTO> {
public:
    void displayMenu(DriverDTO& dto) override {
        while (true) {
            ConsoleUtils::setColor(ConsoleUtils::BLUE);
            cout << "========================================" << endl;
            cout << "||          Driver Menu               ||" << endl;
            cout << "========================================" << endl;
            cout << "|| 1. Withdraw balance                ||" << endl;
            cout << "|| 2. Statistics                      ||" << endl;
            cout << "|| 3. Show your result orders (.csv)  ||" << endl;
            cout << "|| 4. Logout                          ||" << endl;
            cout << "========================================" << endl;
            cout << "|| Your option: ";
            ConsoleUtils::resetColor();

            int choice;
            cin >> choice;

            if (choice == 4) {
                system("cls");
                ConsoleUtils::setColor(ConsoleUtils::GREEN);
                ConsoleUtils::printAnimated("Exiting to the login menu...", 50);
                ConsoleUtils::resetColor();
                break;
            }

            ConsoleUtils::setColor(ConsoleUtils::YELLOW);
            ConsoleUtils::printAnimated("Processing your choice...", 50);
            ConsoleUtils::resetColor();
            dto.call_function(choice);
        }
    }
};


#endif // !DRIVER_MENU_H