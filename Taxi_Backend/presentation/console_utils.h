#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include "../lib/lib.h"

class ConsoleUtils {
public:
    static void setColor(const string& color) {
        cout << color;
    }

    static void resetColor() {
        cout << "\033[0m"; // —брос цвета
    }

    static void printAnimated(const string& text, int delay = 50) {
        for (char ch : text) {
            cout << ch << flush;
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
        cout << endl;
    }

    static const string RED;
    static const string GREEN;
    static const string BLUE;
    static const string YELLOW;
    static const string CYAN;
};

const string ConsoleUtils::RED = "\033[31m";
const string ConsoleUtils::GREEN = "\033[1;32m";
const string ConsoleUtils::BLUE = "\033[1;34m";
const string ConsoleUtils::YELLOW = "\033[1;33m";
const string ConsoleUtils::CYAN = "\033[36m";

#endif // !CONSOLE_UTILS_H