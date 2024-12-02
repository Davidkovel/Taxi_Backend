#ifndef SAVE_USER_BOOKING_ORDERS_SERVICE_H
#define SAVE_USER_BOOKING_ORDERS_SERVICE_H

#include "../domain.h"

class SaveBookingOrdersService
{
private:
    SQLiteOrderRepository* orderRepo;
public:
    SaveBookingOrdersService() = default;
    SaveBookingOrdersService(SQLiteOrderRepository* repo)
        : orderRepo(repo) {}

    void set_query_db(DatabaseProvider* provider)
    {
        this->orderRepo = provider->setOrderRepository();
    }

    void save_to_csv(int user_id, const string& file_path) {
        StyleDecorator::clearScreen();
        auto& logger = logger::Logger::getInstance();
        map<int, tuple<string, string, string, double>> orders = orderRepo->saveUserOrders(user_id);

        ofstream file(file_path);
        logger.info("File opened");
        if (!file.is_open()) {
            logger.error("Error opening file for writing");
            throw exceptions::CSVFileException("Error opening file for writing:" + file_path);
            return;
        }

        // CSV headers
        file << "OrderID,FromAddress,ToAddress,Status,Price\n";

        for (const auto& order : orders) {
            int orderId = order.first;
            string from_address = get<0>(order.second);
            string to_address = get<1>(order.second);
            string status = get<2>(order.second);
            double price = get<3>(order.second);

            file << orderId << "," << from_address << "," << to_address << ","
                << status << "," << price << "\n";
        }

        file.close();
        logger.info("file closed");
        logger.info("Orders saved successfully to " + file_path);
        cout << "\033[1;32m File succesfuly saved \033[0m" << endl;
    }

};

#endif // !SAVE_USER_BOOKING_ORDERS
