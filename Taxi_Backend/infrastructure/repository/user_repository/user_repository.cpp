// SQLiteUserRepository.cpp
#include "user_repository.h"

SQLiteUserRepository::SQLiteUserRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

void SQLiteUserRepository::createUser(const User& user) {
    string sql = "INSERT INTO users (name, age, email, password, role) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, user.age);
    sqlite3_bind_text(stmt, 3, user.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, user.getRole().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw exceptions::DBException("Error adding user to database: " + string(sqlite3_errmsg(dbConn->getConnection())));
    }

    sqlite3_finalize(stmt);
}

User* SQLiteUserRepository::findUserByEmail(const string& email) {
    string sql = "SELECT id, name, age, email, password, balance, role FROM users WHERE email = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        // Подготовка SQL-запроса
        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw exceptions::DBException("Failed to prepare SQL query", sqlite3_errmsg(dbConn->getConnection()));
        }

        // Привязка параметра email
        if (sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
            sqlite3_finalize(stmt);
            throw exceptions::DBException("Failed to bind email parameter", sqlite3_errmsg(dbConn->getConnection()));
        }

        // Выполнение запроса
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Извлечение данных из результата
            int userId = sqlite3_column_int(stmt, 0); // Извлечение user_id
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);
            string retrievedEmail = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            double balance = sqlite3_column_double(stmt, 5);
            string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

            // Финализация запроса
            sqlite3_finalize(stmt);

            int* userIdPtr = new int(userId);
            if (role == "Passenger") {
                return new Passenger(userIdPtr, name, age, retrievedEmail, password, balance, role);
            }
            else if (role == "Driver") {
                return new Driver(userIdPtr, name, age, retrievedEmail, password, balance, role);
            }
            else {
                throw exceptions::DBException("Unknown role in database", role.c_str());
            }
        }

        // Пользователь не найден
        sqlite3_finalize(stmt);
        return nullptr;

    }
    catch (const exception& ex) {
        if (stmt) sqlite3_finalize(stmt);
        throw; // Повторное выбрасывание исключения
        throw exceptions::DBException("Error fetching user by ID", ex.what());
    }
}

bool SQLiteUserRepository::userExists(const string& email)
{
    string sql = "SELECT COUNT(*) FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return exists;
}

User* SQLiteUserRepository::findUserById(int user_id) {
    try {
        string sql = "SELECT name, age, email, password, balance, role FROM users WHERE id = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw exceptions::DBException("Failed to prepare SQL query", sqlite3_errmsg(dbConn->getConnection()));
        }

        sqlite3_bind_int(stmt, 1, user_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int age = sqlite3_column_int(stmt, 1);
            string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            double balance = sqlite3_column_double(stmt, 4);
            string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            sqlite3_finalize(stmt);

            int* userIdPtr = new int(user_id);
            return new Passenger(userIdPtr, name, age, email, password, balance, role);
        }

        sqlite3_finalize(stmt);
        return nullptr; // User has not found
    }
    catch (const exception& e) {
        throw exceptions::DBException("Error fetching user by ID", e.what());
    }
}

void SQLiteUserRepository::updateUserBalance(const string& email, double new_balance) {
    try {
        if (sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to begin transaction");
        }

        string sql = "UPDATE users SET balance = ? WHERE email = ?;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare statement");
        }
        sqlite3_bind_double(stmt, 1, new_balance);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw runtime_error("Failed to update balance");
        }
        sqlite3_finalize(stmt);

        if (sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to commit transaction");
        }
    }
    catch (const exception& ex) {
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        throw exceptions::DBException("Failed to update user balance", ex.what());
    }
}


bool SQLiteUserRepository::deductUserBalance(int user_id, double amount)
{
    try {
        // Start Transaction
        if (sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw exceptions::DBException("Failed to begin transaction", sqlite3_errmsg(dbConn->getConnection()));
        }

        string getBalanceSql = "SELECT balance FROM users WHERE id = ?;";
        sqlite3_stmt* getBalanceStmt;

        if (sqlite3_prepare_v2(dbConn->getConnection(), getBalanceSql.c_str(), -1, &getBalanceStmt, nullptr) != SQLITE_OK) {
            throw exceptions::DBException("Failed to prepare SQL query to get balance", sqlite3_errmsg(dbConn->getConnection()));
        }

        sqlite3_bind_int(getBalanceStmt, 1, user_id);

        double currentBalance = 0.0;
        if (sqlite3_step(getBalanceStmt) == SQLITE_ROW) {
            currentBalance = sqlite3_column_double(getBalanceStmt, 0);
        }
        else {
            sqlite3_finalize(getBalanceStmt);
            throw exceptions::DBException("User not found with the given ID", to_string(user_id).c_str());
        }

        sqlite3_finalize(getBalanceStmt);

        if (currentBalance < amount) {
            throw exceptions::DBException("Insufficient balance", "Attempted to deduct more than available");
        }

        double newBalance = currentBalance - amount;

        string updateBalanceSql = "UPDATE users SET balance = ? WHERE id = ?;";
        sqlite3_stmt* updateStmt;

        if (sqlite3_prepare_v2(dbConn->getConnection(), updateBalanceSql.c_str(), -1, &updateStmt, nullptr) != SQLITE_OK) {
            throw exceptions::DBException("Failed to prepare SQL query to update balance", sqlite3_errmsg(dbConn->getConnection()));
        }

        sqlite3_bind_double(updateStmt, 1, newBalance);
        sqlite3_bind_int(updateStmt, 2, user_id);

        if (sqlite3_step(updateStmt) != SQLITE_DONE) {
            sqlite3_finalize(updateStmt);
            throw exceptions::DBException("Failed to execute SQL query to update balance", sqlite3_errmsg(dbConn->getConnection()));
        }

        sqlite3_finalize(updateStmt);

        // Commit Transaction
        if (sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw exceptions::DBException("Failed to commit transaction", sqlite3_errmsg(dbConn->getConnection()));
        }

        return true;
    }
    catch (const exception& e) {
        // Rollback Transaction
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        throw exceptions::DBException("Error deducting user balance", e.what());
    }
}
