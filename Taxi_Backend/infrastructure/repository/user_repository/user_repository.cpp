// SQLiteUserRepository.cpp
#include "user_repository.h"

SQLiteUserRepository::SQLiteUserRepository(DatabaseConnection* dbConn) : dbConn(dbConn) {}

void SQLiteUserRepository::createUser(const User& user) {
    string sql = "INSERT INTO users (name, age, email, role) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(dbConn->getConnection(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, user.age);
    sqlite3_bind_text(stmt, 3, user.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, user.getRole().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw exceptions::DBException("Error adding user to database: " + string(sqlite3_errmsg(dbConn->getConnection())));
    }

    sqlite3_finalize(stmt);
}

User* SQLiteUserRepository::findUserByEmail(const string& email) {
    return nullptr;
}