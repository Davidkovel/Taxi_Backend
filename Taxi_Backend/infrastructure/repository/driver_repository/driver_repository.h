// SQLiteUserRepository.h
#ifndef SQLITE_DRIVER_REPOSITORY_H
#define SQLITE_DRIVER_REPOSITORY_H

#include "../../../domain/domain.h"
#include "../../database/db_connection.h"
#include "../../../application/interfaces/driver_repository_interface.h"
#include "../../../lib/exceptions/exception.h"

class SQLiteDriverRepository : public IDriverRepository {
public:
    SQLiteDriverRepository(DatabaseConnection* dbConn);
    vector<int> getAvailableDriverIds() override;
    void updateDriverBalance(int driverId, double newBalance) override;
private:
    DatabaseConnection* dbConn;
};

#endif // SQLITE_DRIVER_REPOSITORY_H