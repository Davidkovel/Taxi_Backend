#ifndef BOOKING_H
#define BOOKING_H

#include "../domain/domain.h"

class Booking {
private:
    string fromAddress;
    string toAddress;
    double cost;
public:
    Booking() = default;
    Booking(const string& from, const string& to, double cost)
        : fromAddress(from), toAddress(to), cost(cost) {}

    void bookTaxi(const string& from, const string& to) {
        double fare = calculateFare(from, to);
        cout << "Taxi booked from " << from << " to " << to << " with a fare of " << fare << " USD." << endl;
    }

    double calculateFare(const string& from, const string& to) {
        this->cost = 10.0 + (to.length() - from.length()) * 0.5;
        cout << "Price will be " << this->cost << endl;
        return this->cost;
    }

    void set_information_for_booking_taxi()
    {
        string from, to;
        cout << "Enter start address: ";
        cin.ignore();
        getline(cin, from);
        cout << "Enter destination address: ";
        getline(cin, to);

        this->fromAddress = from;
        this->toAddress = to;
        calculateFare(fromAddress, toAddress);
    }

    void displayBookingInfo() const {
        cout << "Booking from: " << fromAddress << endl;
        cout << "To: " << toAddress << endl;
        cout << "Cost: $" << cost << endl;
    }

};

#endif // BOOKING_H