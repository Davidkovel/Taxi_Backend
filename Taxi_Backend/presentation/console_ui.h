#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "../presentation/user_interface.h"
#include "../use_cases/dto.h"
#include "../infrastructure/db_provider.h"

class CONSOLE_UI : virtual public IUser {
private:
    DTO dto;
public:
    CONSOLE_UI()
    {
       // this->obs_obj = obj;
    }

    CONSOLE_UI(DatabaseProvider* provider) : dto(provider) {}

    void display_terminal() override {
        cout << "Choose an option:" << endl;
        cout << "1. Book a taxi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Register" << endl;

        cout << "Your option: ";
        int choice;
        cin >> choice;

        dto.call_function(choice);
    }

    //void registerUser(User* user) override {
    //    // Реализация логики регистрации пользователя
    //    cout << "User registered: " << user->name << endl;
    //}

    //User* login(const string& email, const string& password) override {
    //    // Реализация логики входа пользователя
    //    cout << "User login attempted with email: " << email << endl;
    //    return nullptr; // Замените логику по мере необходимости
    //}

};

#endif // CONSOLE_UI_H
