// SQLiteOrderRepository.cpp
#include "order_repos.h"

SQLiteOrderRepository::SQLiteOrderRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

void SQLiteOrderRepository::add_order(int user_id, const string& from_address, const string& to_address, const string& status, double price) {
    string sql = "INSERT INTO orders (user_id, from_address, to_address, status, price) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(dbConn->getConnection()) << endl;
        return;
    }

    // Bind parameters
    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, from_address.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, to_address.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 5, price);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error adding order to database: " << sqlite3_errmsg(dbConn->getConnection()) << endl;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
}
