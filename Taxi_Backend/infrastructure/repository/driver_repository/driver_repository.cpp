// SQLiteDriverRepository.cpp
#include "driver_repository.h"

SQLiteDriverRepository::SQLiteDriverRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

vector<int> SQLiteDriverRepository::getAvailableDriverIds() {
    vector<int> driverIds;
    sqlite3_stmt* stmt = nullptr;
    string sql = "SELECT driver_id FROM drivers WHERE busy = 0;";

    try {
        sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare SQL statement for fetching driver IDs: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int driverId = sqlite3_column_int(stmt, 0);
            driverIds.push_back(driverId);
        }

        sqlite3_finalize(stmt);

        sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr);
    }
    catch (const exception& ex) {
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        if (stmt) sqlite3_finalize(stmt);
        throw runtime_error(string("Error fetching driver IDs: ") + ex.what());
    }

    return driverIds;
}

void SQLiteDriverRepository::updateDriverBalance(int driverId, double newBalance) {
    sqlite3_stmt* stmt = nullptr; // Инициализация stmt
    string sql = "UPDATE users SET balance = ? WHERE id = ?;";

    try {
        // Начинаем транзакцию
        sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare SQL statement for updating driver balance: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }

        // Привязываем параметры
        sqlite3_bind_double(stmt, 1, newBalance); // Новый баланс
        sqlite3_bind_int(stmt, 2, driverId);      // ID водителя

        // Выполняем запрос
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw runtime_error("Failed to execute SQL statement for updating driver balance: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }

        sqlite3_finalize(stmt);

        // Завершаем транзакцию
        sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr);
    }
    catch (const exception& ex) {
        // Откатываем транзакцию в случае ошибки
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        if (stmt) sqlite3_finalize(stmt);
        throw runtime_error(string("Error updating driver balance: ") + ex.what());
    }
}

