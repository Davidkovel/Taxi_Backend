#ifndef BOOKING_USE_CASE_H
#define BOOKING_USE_CASE_H

#include "../services/booking_service.h"

class BookingUseCase {
private:
    BookingService* bookingService;

public:
    BookingUseCase() : bookingService(nullptr) {}

    explicit BookingUseCase(BookingService* service) : bookingService(service) {}

    void initial_queries(DatabaseProvider* dbProvider)
    {
        bookingService->set_query_db(dbProvider);
    }

    void execute() {
        bookingService->set_information_for_booking_taxi();
    }
};

#endif // BOOKING_USE_CASE_H
