// SQLiteUserRepository.h
#ifndef SQLITE_USER_REPOSITORY_H
#define SQLITE_USER_REPOSITORY_H

#include "../../database/db_connection.h"
#include "../../../presentation/repos/interface_user_repository.h"
#include "../../../lib/exceptions/exception.h"

class SQLiteUserRepository : public IUserRepository {
public:
    SQLiteUserRepository(DatabaseConnection* dbConn);
    void createUser(const User& user) override;
    User* findUserByEmail(const string& email) override;
private:
    DatabaseConnection* dbConn;
};

#endif // SQLITE_USER_REPOSITORY_H