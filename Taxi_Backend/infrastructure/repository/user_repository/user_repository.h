// SQLiteUserRepository.h
#ifndef SQLITE_USER_REPOSITORY_H
#define SQLITE_USER_REPOSITORY_H

#include "../../database/db_connection.h"
#include "../../../application/interfaces/user_repository_interface.h"
#include "../../../lib/exceptions/exception.h"

class SQLiteUserRepository : public IUserRepository {
public:
    SQLiteUserRepository(DatabaseConnection* dbConn);
    void createUser(const User& user) override;
    User* findUserByEmail(const string& email) override;
    bool userExists(const string& email) override;
    User* findUserById(int user_id) override;
    void updateUserBalance(const string& email, double amount) override;
    void updateUserBalance(int user_id, double amount) override;
    bool deductUserBalance(int user_id, double amount) override;
    string findUserRoleByEmail(const string& email) override;
    double getUserBalance(int user_id) override;
private:
    DatabaseConnection* dbConn;
};

#endif // SQLITE_USER_REPOSITORY_H