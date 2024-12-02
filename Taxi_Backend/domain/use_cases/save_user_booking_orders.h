#ifndef SAVE_ORDERS_CSV_USE_CASE_H
#define SAVE_ORDERS_CSV_USE_CASE_H

#include "../services/save_orders_to_csv_service.h"

class SaveOrdersCsvUseCase {
private:
    SaveBookingOrdersService* save_booking_orders_service;

public:
    SaveOrdersCsvUseCase() : save_booking_orders_service(nullptr) {}

    explicit SaveOrdersCsvUseCase(SaveBookingOrdersService* service) : save_booking_orders_service(service) {}

    void initial_queries(DatabaseProvider* dbProvider)
    {
        save_booking_orders_service->set_query_db(dbProvider);
    }

    void execute(int user_id, const string& file_name) {
        save_booking_orders_service->save_to_csv(user_id, file_name);
    }
};

#endif // SAVE_ORDERS_CSV_USE_CASE_H
    