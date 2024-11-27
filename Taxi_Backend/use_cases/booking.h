#ifndef BOOKING_H
#define BOOKING_H

#include "../domain/domain.h"
#include "../lib/config.h"
#include "../lib/logger.h"
#include "../infrastructure/repository/order_repository/order_repository.h"
#include "../infrastructure/db_provider.h"
#include "../infrastructure/api_provider.h"
#include "../adapters/session.h"
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
            auto& logger = logger::Logger::getInstance();
            string distance, duration;

            ResponseData result_from_api = calculateDistance->execute(from, to, apiKey);
            
            duration = result_from_api.duration;
            double distance_2 = stod(result_from_api.distance);
            double fare = calculateFare(distance_2);

            bool success = deductFareFromUser(fare);
            if (!success) {
                logger.error("Not enough money");
                cout << "You don't have enough money to pay for the taxi." << endl;
                return;
            }

            orderRepo->add_order(session->getUserId(), from, to, "Completed", fare);

            cout << "Taxi booked from " << from << " to " << to << " with a fare of " << fare << " USD." << endl;
            logger.info("Taxi booked succesfuly");
        }
        catch (const exception& ex) {
            cerr << "Error during booking: " << ex.what() << endl;
        }
    }

    double calculateFare(double distance) {
        this->cost = distance * 0.5;
        cout << "Calculated fare: " << this->cost << " USD." << endl;
        return this->cost;
    }

    bool deductFareFromUser(double fare) {
        try {
            auto& logger = logger::Logger::getInstance();
            if (!userRepo) {
                logger.error("User repository is not initialized");
                throw runtime_error("User repository is not initialized");
            }

            User* user = userRepo->findUserById(session->getUserId());
            if (!user) {
                logger.error("User not found");
                throw runtime_error("User not found");
            }

            if (user->getBalance() < fare) {
                logger.error("Insufficient balance to book the taxi");
                throw runtime_error("Insufficient balance to book the taxi");
                return false;
            }

            double newBalance = user->getBalance() - fare;
            userRepo->updateUserBalance(session->getUserEmail(), newBalance);

            logger.info("Fare deducted successfully");
            cout << "New balance: " << newBalance << endl;
            return true;
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
