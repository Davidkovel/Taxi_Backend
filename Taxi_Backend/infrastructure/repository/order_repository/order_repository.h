// SQLiteUserRepository.h
#ifndef ORDER_REPOS_H
#define ORDER_REPOS_H

#include "../../database/db_connection.h"
#include "../../../application/interfaces/order_repository_interface.h"
#include "../../../lib/exceptions/exception.h"

class SQLiteOrderRepository : public IOrderRepository {
public:
    SQLiteOrderRepository() = default;
    SQLiteOrderRepository(DatabaseConnection* dbConn);
    void add_order(int user_id, const string& from_adress, const string& to_adress, const string& status, double price) override;
    OrderMap saveUserOrders(int user_id) override;
    map<int, int> getDriverOrderStats(int driver_id) override;
private:
    DatabaseConnection* dbConn;
};

#endif // USER_REPOS_H
