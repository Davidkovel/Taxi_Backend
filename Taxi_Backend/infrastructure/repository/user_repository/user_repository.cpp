// SQLiteUserRepository.cpp
#include "user_repository.h"

SQLiteUserRepository::SQLiteUserRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

void SQLiteUserRepository::createUser(const User& user) {
    sqlite3_stmt* stmt = nullptr;
    sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    try {
        // 1. Вставляем данные в базовую таблицу users
        string sqlUsers = "INSERT INTO users (name, age, email, password, role) VALUES (?, ?, ?, ?, ?);";
        sqlite3_prepare_v2(dbConn->getConnection(), sqlUsers.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, user.age);
        sqlite3_bind_text(stmt, 3, user.email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, user.passwordHash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, user.getRole().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw exceptions::DBException("Error adding user to database: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }
        sqlite3_finalize(stmt);

        // 2. Получаем ID нового пользователя
        int userId = static_cast<int>(sqlite3_last_insert_rowid(dbConn->getConnection()));

        // 3. Вставляем данные в таблицы passengers или drivers в зависимости от роли
        if (user.getRole() == "Passenger") {
            string sqlPassengers = "INSERT INTO passengers (passenger_id, balance) VALUES (?, ?);";
            sqlite3_prepare_v2(dbConn->getConnection(), sqlPassengers.c_str(), -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, userId);
            sqlite3_bind_int(stmt, 2, user.balance); // Предполагается, что у User есть поле balance
        }
        else if (user.getRole() == "Driver") {
            string sqlDrivers = "INSERT INTO drivers (driver_id, balance, busy) VALUES (?, ?, ?);";
            sqlite3_prepare_v2(dbConn->getConnection(), sqlDrivers.c_str(), -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, userId);
            sqlite3_bind_int(stmt, 2, user.balance); // Предполагается, что у User есть поле balance
            sqlite3_bind_int(stmt, 3, 0);
        }
        else {
            throw exceptions::DBException("Invalid role: " + user.getRole());
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw exceptions::DBException("Error adding user to role-specific table: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }
        sqlite3_finalize(stmt);

        // 4. Завершаем транзакцию
        sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr);

    }
    catch (const exceptions::DBException& e) {
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        if (stmt) sqlite3_finalize(stmt);
        throw; // Перепросываем исключение
    }
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

        sqlite3_bind_double(stmt, 1, new_balance);  // Привязка нового баланса
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);  // Привязка email

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw runtime_error("Failed to update balance");
        }

        // Освобождение ресурсов
        sqlite3_finalize(stmt);

        // Фиксация транзакции
        if (sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to commit transaction");
        }
    }
    catch (const exception& ex) {
        // Откат транзакции в случае ошибки
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        throw exceptions::DBException("Failed to update user balance", ex.what());
    }
}

void SQLiteUserRepository::updateUserBalance(int user_id, double new_balance) {
    sqlite3_stmt* stmt = nullptr;  // Инициализация stmt значением nullptr
    string sql = "UPDATE users SET balance = ? WHERE id = ?;";  // Исправление названия колонки

    try {
        // Начало транзакции
        if (sqlite3_exec(dbConn->getConnection(), "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to begin transaction");
        }

        // Подготовка SQL запроса
        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare statement: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }

        // Привязка параметров
        sqlite3_bind_double(stmt, 1, new_balance);  // Привязка нового баланса
        sqlite3_bind_int(stmt, 2, user_id);  // Привязка user_id (исправлено на int)

        // Выполнение SQL запроса
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw runtime_error("Failed to update balance: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }

        // Освобождение ресурсов
        sqlite3_finalize(stmt);

        // Фиксация транзакции
        if (sqlite3_exec(dbConn->getConnection(), "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to commit transaction");
        }
    }
    catch (const exception& ex) {
        // Откат транзакции в случае ошибки
        sqlite3_exec(dbConn->getConnection(), "ROLLBACK;", nullptr, nullptr, nullptr);
        if (stmt) sqlite3_finalize(stmt);
        throw exceptions::DBException("Failed to update user balance: " + string(ex.what()));
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


string SQLiteUserRepository::findUserRoleByEmail(const string& email) {
    string sql = "SELECT role FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw exceptions::DBException("Error preparing SQL: " + string(sqlite3_errmsg(dbConn->getConnection())));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    string role;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    else {
        throw exceptions::DBException("No role found for email: " + email);
    }

    sqlite3_finalize(stmt);
    return role;
}

double SQLiteUserRepository::getUserBalance(int user_id) {
    sqlite3_stmt* stmt = nullptr;
    string sql = "SELECT balance FROM users WHERE id = ?;";
    double balance = 0.0;

    try {
        if (sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare SQL statement for fetching user balance: " + string(sqlite3_errmsg(dbConn->getConnection())));
        }

        sqlite3_bind_int(stmt, 1, user_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            balance = sqlite3_column_double(stmt, 0);
        }
        else {
            throw runtime_error("No user found with the given ID.");
        }

        sqlite3_finalize(stmt);
    }
    catch (const exception& ex) {
        if (stmt) sqlite3_finalize(stmt);
        throw runtime_error(string("Error fetching user balance: ") + ex.what());
    }

    return balance;
}
