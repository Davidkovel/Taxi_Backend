#include "../domain/domain.h"
#include "../presentation/auth_console_ui.h"

// db connection
#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/db_provider.h"

#include "../lib/exceptions/exception.h"
int main()
{
    cout << "[INFO] The program started well" << endl;
	//try
	//{
	//}
	//catch (const exceptions::DBException ex)
	//{
	//	cout << "Caught MyCustomExc3eption" << endl;
	//	cout << ex.what();
	//}
    string db_path = "example.db";
    DatabaseProvider dbProvider(db_path);
    AuthConsole auth_console(dbProvider);
    auth_console.displayTerminal();

    return 0;
}
