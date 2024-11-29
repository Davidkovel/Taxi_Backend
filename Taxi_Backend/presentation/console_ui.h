#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "../application/interfaces/i_console_ui.h"
#include "../domain/dto/dto.h"
#include "../infrastructure/db_provider.h"
#include "../adapters/session.h"

#include "driver_menu.h"
#include "passenger_menu.h"

class CONSOLE_UI : virtual public IConsole {
private:
    DatabaseProvider* dbProvider;
public:
    CONSOLE_UI() = default;

    explicit CONSOLE_UI(DatabaseProvider* provider) : dbProvider(provider) {}

    void display_main_menu() override {
        string role = Session::getInstance()->getUserRole();

        if (role == "Passenger") {
            PassengerDTO passengerDto(dbProvider);
            PassengerMenu passengerMenu;
            passengerMenu.displayMenu(passengerDto);
        }
        else if (role == "Driver") {
            DriverDTO driverDto(dbProvider);
            DriverMenu driverMenu;
            driverMenu.displayMenu(driverDto);
        }
        else {
            cout << "Unknown role: " << role << endl;
        }
    }
};

#endif // CONSOLE_UI_H
