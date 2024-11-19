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

    // THESE 2 METHODS ARE TEMPORALLY
    SQLiteUserRepository* createUserRepository(const Passenger& passenger) {
        userRepository.createUser(passenger);
        return &userRepository;
    }

    // Overload to accept another concrete class
    SQLiteUserRepository* createUserRepository(const Driver& driver) {
        userRepository.createUser(driver);
        return &userRepository;
    }

    SQLiteUserRepository* setUserRepository() {
        return &userRepository;
    }

    SQLiteOrderRepository* setOrderRepository() {
        return &orderRepository;
    }
};

#endif // DATABASE_PROVIDER_H
