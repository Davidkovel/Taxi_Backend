#include "../domain/domain.h"
#include "../presentation/auth_console_ui.h"
#include "../lib/logger.h"
// db connection
#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/db_provider.h"

int main()
{
    auto& logger = logger::Logger::getInstance();

    logger.setLoggingEnabled(true);
    logger.info("The application started");

    string db_path = "example.db";
    DatabaseProvider dbProvider(db_path);
    IAuthConsole* authConsole = new AuthConsole(dbProvider);

    authConsole->displayTerminal();
    return 0;
}


/*

���� � ������� PASSENGER � DRIVER �������, ������������ ��� �������� ���� �����
��� ����������� �� �������� ������� ������� ��� USER
� BOOKING.H ��� DEPOSIT �� ����� �� SESSION �������� ����� ���� (������������ ��� ����������� ������)
� ����� ���� ���� ��� �������� �� DRIVER � PASSENGER


����� ������� ���� ��� ������, 
�������� ������ �������� ACID �������� � ����� ������� �� USE TABLE ��� 2 FOREIGN KEY->PASSENGER 
I DRIVER �� ��� ����� ������ �� ��� ����� ��������� ����� � ��� ������ ����� ������� ���������� �������� �� 
�������� �� �� ��� ��� ����� �������� ���������� ���� 

*/