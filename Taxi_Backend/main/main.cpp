#include "../domain/domain.h"
#include "../presentation/console_ui.h"

// db connection
#include "../infrastructure/database/db_connection.h"
#include "../infrastructure/db_provider.h"

int main()
{
    cout << "[INFO] The program started well" << endl;
    string db_path = "example.db";
    DatabaseProvider dbProvider(db_path);
    CONSOLE_UI ui(&dbProvider);

    ui.display_terminal();

    return 0;
}
