//#include "../domain/domain.h"
//#include "../presentation/console_ui.h"
//#include "../use_cases/obs.h"
//
//// db connection
//#include "../infrastructure/database/db_connection.h"
//#include "../infrastructure/repository/db_user_repository.h"
//
//int main()
//{
//    cout << "[INFO] The programm started well" << endl;
//    DatabaseConnection dbConn("example.db");
//    SQLiteUserRepository userRepository(&dbConn);
//
//    CONSOLE_UI ui;
//
//    Passenger passenger = Passenger("David Doen", 22, "john@example.com", "password123");
//    userRepository.createUser(passenger);
//    
//   // ui.display_terminal();
//
//    //cout << "Welcome, " << passenger.name << "! Your role is: " << passenger.getRole() << endl;
//
//    //cout << "Authentication failed!" << endl;
//
//
//    return 0;
//}

//
#include <sqlite3.h>
#include <iostream>
using namespace std;
int main() {
    sqlite3* db;
    int exit = sqlite3_open("taxi_service.db", &db);

    if (exit) {
        cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    else {
        cout << "openeed" << endl;
    }

    //const char* sql = "CREATE TABLE IF NOT EXISTS test ("
    //    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //    "name TEXT NOT NULL, "
    //    "age INTEGER);";
    //char* errorMessage;
    //exit = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);

    //if (exit != SQLITE_OK) {
    //    cerr << "error " << errorMessage << endl;
    //    sqlite3_free(errorMessage);
    //}
    //else {
    //    cout << "Created succesfully!" << endl;
    //}

    sqlite3_close(db); 
    return 0;
}