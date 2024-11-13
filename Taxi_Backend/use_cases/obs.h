#ifndef OBS_H
#define OBS_H

#include "booking.h"

class OBS
{
private:
	Booking booking;
public:
	OBS() = default;

	void call_function(int choice)
	{
		switch (choice)
		{
		case 1:
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

#endif // !OBS_H
