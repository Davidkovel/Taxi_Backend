#ifndef DATABASE_PROVIDER_H
#define DATABASE_PROVIDER_H

#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/repository/user_repository/user_repository.h"
#include "../infrastructure/repository/order_repository/order_repository.h"

class DatabaseProvider {
private:
    DatabaseConnection dbConn;
    SQLiteUserRepository userRepository;
    SQLiteOrderRepository orderRepository;

public:
    DatabaseProvider() = default;

    DatabaseProvider(string path_db)
        : dbConn(path_db),
        userRepository(&dbConn),
        orderRepository(&dbConn) {}

    SQLiteUserRepository& setUserRepository() {
        return userRepository;
    }

    SQLiteOrderRepository* setOrderRepository() {
        return &orderRepository;
    }
};

#endif // DATABASE_PROVIDER_H
