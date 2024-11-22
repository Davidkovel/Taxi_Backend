#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <tuple>
#include <stdexcept>
#include <exception>
#include <iomanip>
#include <sstream>
#include <sqlite3.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>

using namespace std;

namespace exceptions {
    class BaseException;
    class DBException;
    class CSVFileException;
    class ProcessException;
}

using OrderMap = map<int, tuple<string, string, string, double>>;
using json = nlohmann::json;