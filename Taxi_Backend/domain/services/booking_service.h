#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include "../domain.h"
#include "../../lib/config.h"
#include "../../lib/logger.h"
#include "../../application/utils/style_decorator.h"
#include "../../infrastructure/repository/order_repository/order_repository.h"
#include "../../infrastructure/db_provider.h"
#include "../../infrastructure/api_provider.h"
#include "../../adapters/session.h"

#include "calculate_distance_service.h"
#include "user_balance_service.h"

class BookingService {
private:
    string fromAddress;
    string toAddress;
    double cost;
    int user_id;

    SQLiteOrderRepository* orderRepo;
    SQLiteUserRepository* userRepo;
    SQLiteDriverRepository* driverRepo;
    DistanceCalculationService* calculateDistance;
    UserBalanceService* userBalanceService;
public:
    BookingService() = default;
    BookingService(const string& from, const string& to, double cost, int userId, SQLiteOrderRepository* repo)
        : fromAddress(from), toAddress(to), cost(cost), user_id(userId), orderRepo(repo) {}

    void set_query_db(DatabaseProvider* provider)
    {
        this->orderRepo = provider->setOrderRepository();
        this->userRepo = provider->setUserRepository();
        this->driverRepo = provider->setDriverRepository();
    }

    void bookTaxi(string& from, string& to) {
        try {
            auto& logger = logger::Logger::getInstance();
            string distance, duration;

            vector<int> availableDrivers = driverRepo->getAvailableDriverIds();
            if (availableDrivers.empty()) {
                StyleDecorator::printColored("No available taxis at the moment. Please try again later.", StyleDecorator::Color::CYAN);
                logger.error("No available drivers for the booking.");
                return;
            }

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0, availableDrivers.size() - 1);

            int randomIndex = dist(gen);
            int selectedDriverId = availableDrivers[randomIndex];

            StyleDecorator::printColored("Calculating distance and fare...", StyleDecorator::Color::YELLOW);
            ResponseData result_from_api = calculateDistance->calculateDistance(from, to, apiKey);
            
            StyleDecorator::printColored("----------------------------------------", StyleDecorator::Color::YELLOW);
            StyleDecorator::printColored("Distance: " + result_from_api.distance, StyleDecorator::Color::BLUE);
            StyleDecorator::printColored("Duration: " + result_from_api.duration, StyleDecorator::Color::BLUE);

            duration = result_from_api.duration;
            double distance_2 = stod(result_from_api.distance);
            double fare = calculateFare(distance_2);

            bool success = deductFareFromUser(fare);
            if (!success) {
                logger.error("Not enough money");
                StyleDecorator::printColored("You don't have enough money to pay for the taxi.", StyleDecorator::Color::RED);
                return;
            }

            orderRepo->add_order(session->getUserId(), from, to, "Completed", fare);
            orderRepo->add_order(selectedDriverId, from, to, "Completed", fare);

            User* driver = userRepo->findUserById(selectedDriverId);
            if (!driver) {
                throw runtime_error("Driver not found.");
            }

            double newBalanceDriver = driver->getBalance() + fare;
            driverRepo->updateDriverBalance(selectedDriverId, newBalanceDriver);

            cout << endl;
            StyleDecorator::printColored("Fare deducted. New balance: " + to_string(fare), StyleDecorator::Color::GREEN);
            StyleDecorator::printColored("Taxi successfully booked from "+ from + " to " + to, StyleDecorator::Color::GREEN); 
            logger.info("Taxi booked succesfuly");
        }
        catch (const exception& ex) {
            cerr << "Error during booking: " << ex.what() << endl;
        }
    }


    double calculateFare(double distance) {
        this->cost = distance * 0.5;
        StyleDecorator::printColored("Fare: " + to_string(this->cost) + " USD.", StyleDecorator::Color::CYAN);
        StyleDecorator::printColored("----------------------------------------", StyleDecorator::Color::YELLOW);
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
            StyleDecorator::printColored("New balance: $" + to_string(newBalance), StyleDecorator::Color::GREEN);
            return true;
        }
        catch (const exception& e) {
            cerr << "Error deducting fare: " << e.what() << endl;
            throw;
        }
    }

    string getInput(const string& prompt) {
        StyleDecorator::printColoredUserInput(prompt, StyleDecorator::Color::YELLOW);
        string input;
        cin.ignore();
        getline(cin, input);
        return input;
    }

    void set_information_for_booking_taxi() {
        StyleDecorator::clearScreen();
        StyleDecorator::printColored("----------------------------------------", StyleDecorator::Color::YELLOW);

        this->fromAddress = getInput("Enter start address (e.g., Paris): ");
        this->toAddress = getInput("Enter destination address (e.g., London): ");

        cout << endl;

        bookTaxi(fromAddress, toAddress);
    }


    void displayBookingInfo() const {
        StyleDecorator::printColored("Booking from: " + fromAddress, StyleDecorator::Color::CYAN);
        StyleDecorator::printColored("To: " + toAddress, StyleDecorator::Color::CYAN);
        StyleDecorator::printColored("Cost: $" + to_string(cost), StyleDecorator::Color::GREEN);
    }

    ~BookingService() {}
};

#endif // BOOKING_SERVICE_H
