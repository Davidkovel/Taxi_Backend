#include "./domain/domain.h"

int main()
{
	cout << "[INFO] The programm started well" << endl;

    CONSOLE_UI userService;

    Passenger passenger = Passenger("David Doe", 22, "john@example.com", "password123");
    userService.display_terminal();


    //cout << "Welcome, " << passenger.name << "! Your role is: " << passenger.getRole() << endl;

    //cout << "Authentication failed!" << endl;
   

	return 0;
}