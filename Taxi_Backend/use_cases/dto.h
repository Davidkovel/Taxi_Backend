#ifndef DTO_H
#define DTO_H

#include "booking.h"
#include "save_user_booking_orders.h"
#include "../infrastructure/db_provider.h"
#include "../infrastructure/network/api_client_impl.h"

class DTO
{
private:
	Booking booking;
	SaveBookingOrders save_booking;
	DatabaseProvider* dbProvider;
public:
	DTO() = default;
	DTO(DatabaseProvider* provider) : dbProvider(provider) {}

	void call_function(int choice)
	{
		switch (choice)
		{
		case 1:
			booking.set_query_db(dbProvider);
			booking.set_information_for_booking_taxi();
			booking.displayBookingInfo();
			cout << "The order is succesfuly booked. Wait for your taxi" << endl;
			break;
		case 2:
			save_booking.set_query_db(dbProvider);
			save_booking.save_to_csv(0, "user_orders.csv");
			break;

		default:
			cout << "Error choice. Try again!" << endl;
			break;
		}
	}
};

#endif // !DTO_H
