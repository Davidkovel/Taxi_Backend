#ifndef SAVE_USER_BOOKING_ORDERS
#define SAVE_USER_BOOKING_ORDERS

#include "../domain/domain.h"

class SaveBookingOrders
{
private:
	SQLiteOrderRepository* orderRepo;
public:
    SaveBookingOrders() = default;
    SaveBookingOrders(SQLiteOrderRepository* repo)
        : orderRepo(repo) {}

    void set_query_db(DatabaseProvider* provider)
    {
        this->orderRepo = provider->setOrderRepository();
    }
    
    void save_to_csv(int user_id, const string& file_path) {
        map<int, tuple<string, string, string, double>> orders = orderRepo->saveUserOrders(user_id);

        ofstream file(file_path);
        if (!file.is_open()) {
            throw exceptions::CSVFileException("Error opening file for writing: ", file_path);
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
        cout << "Orders saved successfully to " << file_path << endl;
    }

};

#endif // !SAVE_USER_BOOKING_ORDERS
