#include "../domain/domain.h"
#include "../lib/logger.h"

#include "../presentation/auth_console_ui.h"
#include "../infrastructure/db_provider.h"
#include "../infrastructure/database/db_connection.h"

int main()
{
    auto& logger = logger::Logger::getInstance();

    logger.setLoggingEnabled(false);
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