// SQLiteOrderRepository.cpp
#include "order_repository.h"

SQLiteOrderRepository::SQLiteOrderRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

void SQLiteOrderRepository::add_order(int user_id, const string& from_address, const string& to_address, const string& status, double price) {
    string sql = "INSERT INTO orders (user_id, from_adress, to_adress, status, price) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(dbConn->getConnection()) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, from_address.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, to_address.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 5, price);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw exceptions::DBException("Error adding order to database: " + string(sqlite3_errmsg(dbConn->getConnection())));
    }

    sqlite3_finalize(stmt);
}
