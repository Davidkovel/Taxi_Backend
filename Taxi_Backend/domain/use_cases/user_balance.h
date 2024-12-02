#ifndef USER_BALANCE_USE_CASE_H
#define USER_BALANCE_USE_CASE_H

#include "../services/user_balance_service.h"

class UserBalanceUseCase {
private:
    UserBalanceService* user_balance_service;

public:
    UserBalanceUseCase() : user_balance_service(nullptr) {}

    explicit UserBalanceUseCase(UserBalanceService* service)
        : user_balance_service(service) {
        if (!user_balance_service) {
            cerr << "UserBalanceService is not initialized!";
        }
    }

    void execute_deposit() {
        if (!user_balance_service) {
            cerr << "UserBalanceService is not available!";
        }
        user_balance_service->deposit();
    }
    //void initial_queries(DatabaseProvider* dbProvider)
    //{
    //    user_balance_service->set_query_db(dbProvider->setUserRepository());
    //}

    //void execute_deposit() {
    //    user_balance_service->deposit();
    //}

    void execute_withdraw() {
        user_balance_service->withdraw();
    }

    void execute_statistic(int driver_id) {
        user_balance_service->statistic(driver_id);
    }
};

#endif // USER_BALANCE_USE_CASE_H
