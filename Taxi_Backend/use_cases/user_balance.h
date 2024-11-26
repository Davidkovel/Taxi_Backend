#ifndef USER_BALANCE_H
#define USER_BALANCE_H

#include "../domain/domain.h"
#include "../infrastructure/db_provider.h"
#include "../infrastructure/repository/user_repository/user_repository.h"
#include "../adapters/session.h"

class UserBalance
{
private:
    SQLiteUserRepository* userRepo;

    User* updateBalance(int userId, double amount) {
        User* user = userRepo->findUserById(userId);

        if (!user) {
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
        cout << "Enter amount to " << operation << ": ";
        cin >> amount;
        cin.ignore();
        return amount;
    }

public:
	UserBalance() = default;

    void set_query_db(DatabaseProvider* provider)
    {
        this->userRepo = provider->setUserRepository();
    }

    void deposit() {
        try {
            int userId = session->getUserId();
            double amount = promptAmount("deposit");

            if (amount <= 0) {
                throw exceptions::ProcessException("Deposit amount must be greater than zero");
            }

            User* updatedUser = updateBalance(userId, amount);
            cout << "Deposit successful! New balance: " << updatedUser->getBalance() << endl;

            delete updatedUser;
        }
        catch (exception& ex)
        {
            cerr << "Error deposit: " << ex.what() << endl;
        }
    }

    bool deductBalance(int userId, double amount) {
        User* user = userRepo->findUserByEmail("dd");
        if (user == nullptr) {
            cout << "EORORORO NULLTR";
            throw runtime_error("User not found");
        }

        double currentBalance = user->getBalance();
        if (currentBalance < amount) {
            return false;
        }

        double newBalance = currentBalance - amount;
        user->setBalance(newBalance);

        userRepo->updateUserBalance(user->getEmail(), newBalance);
        return true;
    }

    void withdraw() {
        try {
            int userId = session->getUserId();
            double amount = promptAmount("withdraw");

            if (amount <= 0) {
                throw exceptions::ProcessException("Withdrawal amount must be greater than zero");
            }

            User* updatedUser = updateBalance(userId, -amount);
            cout << "Withdrawal successful! New balance: " << updatedUser->getBalance() << endl;

            delete updatedUser;

        }
        catch (const exception& ex)
        {
            cerr << "Error withdraw: " << ex.what() << endl;
        }
    }

    ~UserBalance() {}
};


#endif // !USER_BALANCE_H
