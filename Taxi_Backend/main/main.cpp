#include "../domain/domain.h"
#include "../presentation/console_ui.h"
#include "../use_cases/obs.h"

// db connection
#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/repository/db_user_repository.h"
#include <sqlite3.h>

int main()
{
    cout << "[INFO] The programm started well" << endl;
    // CONNECTION DB SECOND COMMIT
    DatabaseConnection dbConn("example.db");

    SQLiteUserRepository userRepository(&dbConn);

    // CONSOLE_UI FIRST COMMIT
    CONSOLE_UI ui;

    Passenger passenger = Passenger("David Doe", 22, "john@example.com", "password123");
    userRepository.createUser(passenger);
    
    ui.display_terminal();


    //cout << "Welcome, " << passenger.name << "! Your role is: " << passenger.getRole() << endl;

    //cout << "Authentication failed!" << endl;


    return 0;
}
