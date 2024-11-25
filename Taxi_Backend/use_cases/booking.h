#ifndef BOOKING_H
#define BOOKING_H

#include "../domain/domain.h"
#include "../lib/config.h"
#include "../infrastructure/repository/order_repository/order_repository.h"
#include "../infrastructure/db_provider.h"
#include "../infrastructure/api_provider.h"
#include "./calculate_distance.h"
#include "./user_balance.h"


class Booking {
private:
    string fromAddress;
    string toAddress;
    double cost;
    int user_id;

    SQLiteOrderRepository* orderRepo;
    SQLiteUserRepository* userRepo;
    CalculateDistance* calculateDistance;
    UserBalance* userBalanceService;
public:
    Booking() = default;
    Booking(const string& from, const string& to, double cost, int userId, SQLiteOrderRepository* repo)
        : fromAddress(from), toAddress(to), cost(cost), user_id(userId), orderRepo(repo) {}

    void set_query_db(DatabaseProvider* provider)
    {
        this->orderRepo = provider->setOrderRepository();
        this->userRepo = provider->setUserRepository();
    }

    void bookTaxi(string& from, string& to) {
        try {
            string distance, duration;

            ResponseData result_from_api = calculateDistance->execute(from, to, apiKey);
            
            duration = result_from_api.duration;
            double distance_2 = stod(result_from_api.distance);
            double fare = calculateFare(distance_2);

            deductFareFromUser(fare);

            orderRepo->add_order(user_id, from, to, "Completed", fare);

            cout << "Taxi booked from " << from << " to " << to << " with a fare of " << fare << " USD." << endl;
        }
        catch (const exception& e) {
            cerr << "Error during booking: " << e.what() << endl;
        }
    }

    double calculateFare(double distance) {
        this->cost = distance * 0.5;
        cout << "Calculated fare: " << this->cost << " USD." << endl;
        return this->cost;
    }

    void deductFareFromUser(double fare) {
        try {
            if (!userRepo) {
                throw runtime_error("User repository is not initialized");
            }

            User* user = userRepo->findUserById(3);
            if (!user) {
                throw runtime_error("User not found");
            }

            if (user->getBalance() < fare) {
                throw runtime_error("Insufficient balance to book the taxi");
            }

            double newBalance = user->getBalance() - fare;
            userRepo->updateUserBalance("dd", newBalance);

            cout << "Fare deducted successfully. New balance: " << newBalance << endl;
        }
        catch (const exception& e) {
            cerr << "Error deducting fare: " << e.what() << endl;
            throw;
        }
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
