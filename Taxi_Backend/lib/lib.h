#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>
#include <sqlite3.h>

using namespace std;

namespace exceptions {
    class ProcessResult;
    class DBException;
    class CSVFileException;
}

using OrderMap = map<int, tuple<string, string, string, double>>;