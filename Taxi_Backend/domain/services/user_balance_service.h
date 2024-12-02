#ifndef USER_BALANCE_SERVICE_H
#define USER_BALANCE_SERVICE_H

#include "../domain.h"
#include "../../adapters/session.h"
#include "../../application/utils/style_decorator.h"
#include "../../infrastructure/db_provider.h"
#include "../../infrastructure/repository/user_repository/user_repository.h"
#include "../../infrastructure/repository/order_repository/order_repository.h"

class UserBalanceService
{
private:
    SQLiteUserRepository* userRepo;
    SQLiteOrderRepository* orderRepo;

    User* updateBalance(int userId, double amount) {
        auto& logger = logger::Logger::getInstance();
        User* user = userRepo->findUserById(userId);

        if (!user) {
            logger.error("User not found");
            throw exceptions::ProcessException("User not found");
        }

        string email = user->getEmail();
        double newBalance = user->getBalance() + amount;
        if (newBalance < 0) {
            throw exceptions::ProcessException("Insufficient balance for this operation");
        }
        user->setBalance(newBalance);

        userRepo->updateUserBalance(email, newBalance);

        return user;
    }

    double promptAmount(const string& operation) {
        double amount;
        StyleDecorator::printColored("========================================", StyleDecorator::Color::YELLOW);
        StyleDecorator::printColoredUserInput("Enter amount to " + operation + ": ", StyleDecorator::Color::YELLOW);
        cin >> amount;
        cin.ignore();
        return amount;
    }

public:
    void set_query_db(DatabaseProvider* provider)
    {
        this->userRepo = provider->setUserRepository();
        this->orderRepo = provider->setOrderRepository();
    }

    void deposit() {
        try {
            StyleDecorator::clearScreen();
            int userId = session->getUserId();
            double amount = promptAmount("deposit");

            if (amount <= 0) {
                throw exceptions::ProcessException("Deposit amount must be greater than zero");
            }

            User* updatedUser = updateBalance(userId, amount);

            StyleDecorator::printColored("----------------------------------------", StyleDecorator::Color::YELLOW);
            StyleDecorator::printColored("Deposit successful!", StyleDecorator::Color::GREEN);
            StyleDecorator::printColored("New balance: $" + to_string(updatedUser->getBalance()) + " USD", StyleDecorator::Color::GREEN);
            StyleDecorator::printColored("----------------------------------------", StyleDecorator::Color::YELLOW);

            delete updatedUser;
        }
        catch (exception& ex)
        {
            cerr << "Error deposit: " << ex.what() << endl;
        }
    }

    bool deductBalance(int userId, double amount) {
        User* user = userRepo->findUserByEmail(session->getUserEmail());
        if (user == nullptr) {
            throw runtime_error("User not found");
        }

        double currentBalance = user->getBalance();
        if (currentBalance < amount) {
            return false;
        }

        double newBalance = currentBalance - amount;
        user->setBalance(newBalance);

        userRepo->updateUserBalance(user->getEmail(), newBalance);
        delete user;
        return true;
    }

    void withdraw() {
        try {
            StyleDecorator::clearScreen();
            int userId = session->getUserId();
            double amount = promptAmount("withdraw");

            if (amount <= 0) {
                throw exceptions::ProcessException("Withdrawal amount must be greater than zero");
            }

            bool success = deductBalance(userId, amount);
            if (success) {
                StyleDecorator::printColored("Withdrawal successful!", StyleDecorator::Color::GREEN);
            }
            else {
                StyleDecorator::printColored("Insufficient balance for withdrawal", StyleDecorator::Color::RED);
            }

        }
        catch (const exception& ex)
        {
            StyleDecorator::printColored("Error withdraw: " + string(ex.what()), StyleDecorator::Color::RED);
        }
    }


    double statistic(int driver_id)
    {
        try {
            StyleDecorator::clearScreen();

            double earned_money = userRepo->getUserBalance(driver_id);
            StyleDecorator::printColored("Congratulation you earned: " + to_string(earned_money), StyleDecorator::Color::GREEN);
            map<int, int> statsMap = orderRepo->getDriverOrderStats(driver_id);

            if (statsMap.find(driver_id) == statsMap.end()) {
                cout << "No statistics found for driver with ID: " << driver_id << endl;
                return 0.0;
            }

            int totalOrders = statsMap[driver_id];

            StyleDecorator::printColored("Driver Statistics: ", StyleDecorator::Color::BLUE);
            StyleDecorator::printColored("- Bank account: " + to_string(earned_money), StyleDecorator::Color::BLUE);
            StyleDecorator::printColored("- Total orders: " + to_string(totalOrders), StyleDecorator::Color::BLUE);

            return earned_money;
        }
        catch (const exception& ex) {
            StyleDecorator::printColored("Error retrieving statistics: " + string(ex.what()), StyleDecorator::Color::RED);
            return 0.0;
        }
    }


    ~UserBalanceService() {}
};


#endif // !USER_BALANCE_SERVICE_H
