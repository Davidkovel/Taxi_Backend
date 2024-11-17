// SQLiteUserRepository.h
#ifndef USER_REPOS_H
#define USER_REPOS_H

#include "../../database/db_connection.h"
#include "../../../presentation/repos/interface_user_repository.h"

// #include "../../application/interfaces/IUserRepository.h"
// #include "../database/DatabaseConnection.h"

class SQLiteUserRepository : public IUserRepository {
public:
    SQLiteUserRepository(DatabaseConnection* dbConn);
    void createUser(const User& user) override;
    User* findUserByEmail(const string& email) override;
private:
    DatabaseConnection* dbConn;
};

#endif // USER_REPOS_H