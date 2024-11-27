#ifndef DTO_H
#define DTO_H

#include "../../infrastructure/db_provider.h"
#include "../../infrastructure/network/api_client_impl.h"
#include "../../adapters/session.h"

#include "booking.h"
#include "save_user_booking_orders.h"
#include "user_balance.h"

class DTO
{
private:
	Booking booking;
	SaveBookingOrders save_booking;
	UserBalance user_balance;
	DatabaseProvider* dbProvider;
	Session* session = Session::getInstance();
public:
	DTO() = default;
	DTO(DatabaseProvider* provider) : dbProvider(provider) {}

	void call_function(int choice)
	{
		ensure_initialized();

		switch (choice)
		{
		case 1:
			booking.set_information_for_booking_taxi();
			break;
		case 2:
			user_balance.deposit();
			break;
		case 3:
			save_booking.save_to_csv(session->getUserId(), "user_orders.csv");
			break;

		default:
			cout << "Error choice. Try again!" << endl;
			break;
		}
	}

	void ensure_initialized()
	{
		booking.set_query_db(dbProvider);
		user_balance.set_query_db(dbProvider);
		save_booking.set_query_db(dbProvider);
	}

};

#endif // !DTO_H
