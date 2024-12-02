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

мюдн б рюакхже PASSENGER х DRIVER янгдюрэ, онкэгнбюрекэ яюл бшахпюер йххл ярюрэ
опх пецхярпюжхъ лш янупюмъл ямювюкю рюакхжс йюй USER
б BOOKING.H опх DEPOSIT лш асдел нр SESSION онксвюрэ йюйсч пнкэ (онкэгнбюрекэ опх пецхярпюжхх бшапюк)
ю рюйфе лемч мюдн дкъ нредэмшу нр DRIVER х PASSENGER


оняке ядекюмн тхвс опн нокюрс, 
ядексыхи ондунд днаюбхрэ ACID цюпюмрхи ю рюйфе днаюбхр нр USE TABLE еые 2 FOREIGN KEY->PASSENGER 
I DRIVER мн рел яюлшл йюфдши хг мху асдер нрдекэмши гюйюг х опх кнцхмю асдер ядекюмн яоежхюкэмн опнбепйю мю 
бндхрекэ кх рш хкх мер врнаш онйюгюрэ яоежхюкэмн лемч 

*/