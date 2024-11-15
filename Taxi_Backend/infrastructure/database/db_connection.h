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
        }
    }

    sqlite3* getConnection()
    {
        return db;
    }

    ~DatabaseConnection()
    {
        sqlite3_close(db);
    }
};

#endif // DATABASE_CONNECTION_H
