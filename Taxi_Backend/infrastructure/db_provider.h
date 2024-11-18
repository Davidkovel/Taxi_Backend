#ifndef DATABASE_PROVIDER_H
#define DATABASE_PROVIDER_H

#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/repository/db_user_repository.h"
#include "../infrastructure/repository/order_repository.h"

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

    SQLiteUserRepository* createUserRepository(const Passenger& passenger) {
        userRepository.createUser(passenger);
        return &userRepository;
    }

    // Overload to accept another concrete class
    SQLiteUserRepository* createUserRepository(const Driver& driver) {
        userRepository.createUser(driver);
        return &userRepository;
    }

    SQLiteOrderRepository* createOrderRepository(int user_id, const string& from_adress, const string& to_adress, const string& status, double price) {
        orderRepository.add_order(user_id, from_adress, to_adress, status, price);
        return &orderRepository;
    }

    SQLiteOrderRepository* setOrderRepository() {
        return &orderRepository;
    }
};

#endif // DATABASE_PROVIDER_H
