#ifndef BOOKING_H
#define BOOKING_H

#include "../domain/domain.h"
#include "../infrastructure/repository/order_repository.h"
#include "../infrastructure/db_provider.h"

class Booking {
private:
    string fromAddress;
    string toAddress;
    double cost;
    SQLiteOrderRepository* orderRepo;
    int user_id;
public:
    Booking() = default;
    Booking(const string& from, const string& to, double cost, SQLiteOrderRepository* repo, int userId)
        : fromAddress(from), toAddress(to), cost(cost), orderRepo(repo), user_id(userId) {}

    void set_query_db(DatabaseProvider* provider)
    {
        this->orderRepo = provider->setOrderRepository();
    }

    void bookTaxi(const string& from, const string& to) {
        double fare = calculateFare(from, to);
        cout << "Taxi booked from " << from << " to " << to << " with a fare of " << fare << " USD." << endl;
        orderRepo->add_order(user_id, from, to, "Completed", fare);
    }

    double calculateFare(const string& from, const string& to) {
        this->cost = 10; // TEMPORALLY
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
        bookTaxi(from, to);
    }

    void displayBookingInfo() const {
        cout << "Booking from: " << fromAddress << endl;
        cout << "To: " << toAddress << endl;
        cout << "Cost: $" << cost << endl;
    }

};

#endif // BOOKING_H
