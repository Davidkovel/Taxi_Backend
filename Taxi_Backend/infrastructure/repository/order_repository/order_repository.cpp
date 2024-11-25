// SQLiteOrderRepository.cpp
#include "order_repository.h"

SQLiteOrderRepository::SQLiteOrderRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

void SQLiteOrderRepository::add_order(int user_id, const string& from_address, const string& to_address, const string& status, double price) {
    try {
        // Start Transaction
        if (sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to begin transaction");
        }

        string sql = "INSERT INTO orders (user_id, from_adress, to_adress, status, price) VALUES (?, ?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare statement");
        }
        sqlite3_bind_int(stmt, 1, user_id);
        sqlite3_bind_text(stmt, 2, from_address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, to_address.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 5, price);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw runtime_error("Failed to insert order");
        }
        sqlite3_finalize(stmt);

        // Commit Transaction
        if (sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to commit transaction");
        }
    }
    catch (const exception& ex) {
        // Rollback Transaciton
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        throw exceptions::DBException("Error deducting user balance", ex.what());
    }
}


OrderMap SQLiteOrderRepository::saveUserOrders(int user_id) {
    OrderMap ordersMap;
    string sql = "SELECT order_id, from_adress, to_adress, status, price FROM orders WHERE user_id = ?;";
    sqlite3_stmt* stmt;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw exceptions::DBException("Failed to prepare statement : " + string(sqlite3_errmsg(dbConn->getConnection())));
        return ordersMap;
    }

    // Bind the user_id parameter
    if (sqlite3_bind_int(stmt, 1, user_id) != SQLITE_OK) {
        throw exceptions::DBException("Failed to bind user_id: " + string(sqlite3_errmsg(dbConn->getConnection())));
        sqlite3_finalize(stmt);
        return ordersMap;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int order_id = sqlite3_column_int(stmt, 0);
        string from_address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string to_address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        double price = sqlite3_column_double(stmt, 4);

        ordersMap[order_id] = make_tuple(from_address, to_address, status, price);
    }

    sqlite3_finalize(stmt);

    return ordersMap;
}