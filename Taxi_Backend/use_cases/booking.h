#ifndef BOOKING_H
#define BOOKING_H

#include "../domain/domain.h"
#include "../lib/config.h"
#include "../infrastructure/repository/order_repository/order_repository.h"
#include "../infrastructure/db_provider.h"
#include "../infrastructure/api_provider.h"
#include "./calculate_distance.h"


class Booking {
private:
    string fromAddress;
    string toAddress;
    double cost;
    SQLiteOrderRepository* orderRepo;
    int user_id;
    CalculateDistance* calculateDistance;
public:
    Booking() = default;
    Booking(const string& from, const string& to, double cost, SQLiteOrderRepository* repo, int userId)
        : fromAddress(from), toAddress(to), cost(cost), orderRepo(repo), user_id(userId) {}

    void set_query_db(DatabaseProvider* provider)
    {
        this->orderRepo = provider->setOrderRepository();
    }

    //void set_initialize_calculation(APIClientImpl* api_client)
    //{
    //    this->calculateDistance = api_client->performRequest();
    //}

    void bookTaxi(string& from, string& to) {
        try {
            string distance, duration;

            ResponseData result_from_api = calculateDistance->execute(from, to, apiKey);
            
            duration = result_from_api.duration;
            double distance_2 = stod(result_from_api.distance);
            double fare = calculateFare(distance_2);

            cout << "Taxi booked from " << from << " to " << to << " with a fare of " << fare << " USD." << endl;

            orderRepo->add_order(user_id, from, to, "Completed", fare);
        }
        catch (const exception& e) {
            cerr << "Error during booking: " << e.what() << endl;
        }
    }

    double calculateFare(double distance) {
        // Пример расчёта стоимости на основе расстояния
        this->cost = distance * 0.5; // Стоимость за 1 км
        cout << "Calculated fare: " << this->cost << " USD." << endl;
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
