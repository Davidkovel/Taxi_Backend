#ifndef DTO_H
#define DTO_H

#include "booking.h"
#include "save_user_booking_orders.h"
#include "../infrastructure/db_provider.h"

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
		case 2:
			save_booking.set_query_db(dbProvider);
			save_booking.save_to_csv(0, "user_orders.csv");

		default:
			break;
		}


        //switch (choice) {
//case 1:
//    bookTaxi(); // ��������� ���������� ������������ �����
//    break;
//case 2:
//    loginUser(); // ����� �������� ������ �����
//    break;
//case 3:
//    registerUser(); // ����� �������� ������ �����������
//    break;
//default:
//    cout << "Invalid choice" << endl;
//}
	}
};

#endif // !DTO_H
