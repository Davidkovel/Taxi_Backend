// IOrderRepository.h
#ifndef IORDER_REPOSITORY_H
#define IORDER_REPOSITORY_H

#include "../../domain/domain.h" // temporaly directory path -> the real directory is user.h

class IOrderRepository {
public:
    virtual void add_order(int user_id, const string& from_address, const string& to_address, const string& status, double price) = 0;
    virtual OrderMap saveUserOrders(int user_id) = 0;
    virtual ~IOrderRepository() = default;
};

#endif // IORDER_REPOSITORY_H
