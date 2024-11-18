#ifndef DTO_H
#define DTO_H

#include "booking.h"
#include "../infrastructure/db_provider.h"

class DTO
{
private:
	Booking booking;
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
		default:
			break;
		}


        //switch (choice) {
//case 1:
//    bookTaxi(); // запускаем функционал бронирования такси
//    break;
//case 2:
//    loginUser(); // можно добавить логику входа
//    break;
//case 3:
//    registerUser(); // можно добавить логику регистрации
//    break;
//default:
//    cout << "Invalid choice" << endl;
//}
	}
};

#endif // !DTO_H
