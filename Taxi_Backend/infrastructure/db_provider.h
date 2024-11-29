#ifndef DATABASE_PROVIDER_H
#define DATABASE_PROVIDER_H

#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/repository/user_repository/user_repository.h"
#include "../infrastructure/repository/driver_repository/driver_repository.h"
#include "../infrastructure/repository/order_repository/order_repository.h"

class DatabaseProvider {
private:
    DatabaseConnection dbConn;
    SQLiteUserRepository userRepository;
    SQLiteDriverRepository driverRepository;
    SQLiteOrderRepository orderRepository;

public:
    DatabaseProvider() = default;

    DatabaseProvider(string path_db)
        : dbConn(path_db),
        userRepository(&dbConn),
        driverRepository(&dbConn),
        orderRepository(&dbConn) {}
    
    // TEMPORALLY METHOD
    SQLiteUserRepository& setUserRepositoryForConsole() {
        return userRepository;
    }

    SQLiteUserRepository* setUserRepository() {
        return &userRepository;
    }

    SQLiteDriverRepository* setDriverRepository() {
        return &driverRepository;
    }

    SQLiteOrderRepository* setOrderRepository() {
        return &orderRepository;
    }
};

#endif // DATABASE_PROVIDER_H
