#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>
#include <stdexcept>
#include <sqlite3.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;

namespace exceptions {
    class ProcessResult;
    class DBException;
    class CSVFileException;
}

using OrderMap = map<int, tuple<string, string, string, double>>;
using json = nlohmann::json;