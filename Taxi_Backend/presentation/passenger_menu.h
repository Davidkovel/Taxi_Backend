#ifndef PASSENGER_MENU_H
#define PASSENGER_MENU_H

#include "../application/interfaces/i_menu.h"
#include "console_utils.h"

class PassengerMenu : public IMenu<PassengerDTO> {
public:
    void displayMenu(PassengerDTO& dto) override{
        while (true) {
            ConsoleUtils::setColor(ConsoleUtils::BLUE);
            cout << "========================================" << endl;
            cout << "||         Passenger Menu             ||" << endl;
            cout << "========================================" << endl;
            cout << "|| 1. Book a taxi                     ||" << endl;
            cout << "|| 2. Deposit balance                 ||" << endl;
            cout << "|| 3. Show your booking orders (.csv) ||" << endl;
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

#endif // !PASSENGER_MENU_H