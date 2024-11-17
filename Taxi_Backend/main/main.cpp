#include "../domain/domain.h"
#include "../presentation/console_ui.h"
#include "../use_cases/obs.h"

// db connection
#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/repository/db_user_repository.h"
#include "../infrastructure/repository/order_repository.h"

int main()
{
    cout << "[INFO] The programm started well" << endl;
    DatabaseConnection dbConn("example.db");
    SQLiteUserRepository userRepository(&dbConn);
    SQLiteOrderRepository orderRepository(&dbConn);

    CONSOLE_UI ui;

    // Creation user to db ---
    // Passenger passenger = Passenger("David Doen", 22, "john@example.com", "password123");
    // userRepository.createUser(passenger);
    
    // Creation order to db ---
    Booking booking("Start Address", "Destination Address", 0.0, &orderRepository, 1);
    booking.set_information_for_booking_taxi();

    // ui.display_terminal();

    return 0;
}

////
//#include <sqlite3.h>
//#include <iostream>
//using namespace std;
//int main() {
//    sqlite3* db;
//    int exit = sqlite3_open("taxi_service.db", &db);
//
//    if (exit) {
//        cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << endl;
//        return -1;
//    }
//    else {
//        cout << "openeed" << endl;
//    }
//
//    //const char* sql = "CREATE TABLE IF NOT EXISTS test ("
//    //    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//    //    "name TEXT NOT NULL, "
//    //    "age INTEGER);";
//    //char* errorMessage;
//    //exit = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
//
//    //if (exit != SQLITE_OK) {
//    //    cerr << "error " << errorMessage << endl;
//    //    sqlite3_free(errorMessage);
//    //}
//    //else {
//    //    cout << "Created succesfully!" << endl;
//    //}
//
//    sqlite3_close(db); 
//    return 0;
//}