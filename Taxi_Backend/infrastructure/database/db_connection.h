// DatabaseConnection.h
#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include "../../domain/domain.h"

class DatabaseConnection {
private:
    sqlite3* db;
public:
    DatabaseConnection(const string& dbName)
    {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
            db = nullptr;
        }
        else {
            // Enable WAL mode to ensure durability -> ACID
            if (sqlite3_exec(db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, nullptr) != SQLITE_OK) {
                cerr << "Error setting WAL mode: " << sqlite3_errmsg(db) << endl;
            }
        }
    }

    sqlite3* getConnection()
    {
        return db;
    }

    void closeConnection()
    {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    ~DatabaseConnection()
    {
        closeConnection();
    }
};

#endif // DATABASE_CONNECTION_H
