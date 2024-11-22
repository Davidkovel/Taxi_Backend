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
    string sql = "SELECT name, age, email, password, role FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int age = sqlite3_column_int(stmt, 1);
        string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        sqlite3_finalize(stmt);

        if (role == "Passenger") {
            return new Passenger(name, age, email, password, role);
        }
        else if (role == "Driver") {
            return new Driver(name, age, email, password, role);
        }
    }

    sqlite3_finalize(stmt);
    return nullptr;
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