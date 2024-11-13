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

#endif // !OBS_H
