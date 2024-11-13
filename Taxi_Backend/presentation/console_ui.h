#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "../presentation/user_interface.h"
#include "../use_cases/obs.h"

class CONSOLE_UI : virtual public IUser {
private:
    OBS obs;
public:
    CONSOLE_UI()
    {
       // this->obs_obj = obj;
    }

    void display_terminal() override {
        // OBS obs;
        cout << "Choose an option:" << endl;
        cout << "1. Book a taxi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Register" << endl;

        cout << "Your option: ";
        int choice;
        cin >> choice;

        obs.call_function(choice);
    }

    void registerUser(User* user) override {
        // ���������� ������ ����������� ������������
        cout << "User registered: " << user->name << endl;
    }

    User* login(const string& email, const string& password) override {
        // ���������� ������ ����� ������������
        cout << "User login attempted with email: " << email << endl;
        return nullptr; // �������� ������ �� ���� �������������
    }

};

#endif // CONSOLE_UI_H
