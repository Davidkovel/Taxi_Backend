#ifndef STYLE_DECORATOR_H
#define STYLE_DECORATOR_H

#include "../../lib/lib.h"

class StyleDecorator {
public:
    enum class Color {
        DEFAULT,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        CYAN
    };

    static void setColor(Color color) {
        switch (color) {
        case Color::RED: cout << "\033[31m"; break;
        case Color::GREEN: cout << "\033[1;32m"; break;
        case Color::YELLOW: cout << "\033[1;33m"; break;
        case Color::BLUE: cout << "\033[1;34m"; break;
        case Color::CYAN: cout << "\033[36m"; break;
        case Color::DEFAULT: cout << "\033[0m"; break;
        }
    }

    static void resetColor() {
        cout << "\033[0m";
    }

    static void printColored(const string& message, Color color) {
        setColor(color);
        cout << message << endl;
        resetColor();
    }

    static void printColoredUserInput(const string& message, Color color) {
        setColor(color);
        cout << message;
        resetColor();
    }

    static void printAnimated(const string& message, int delayMs = 50, Color color = Color::DEFAULT) {
        setColor(color);
        for (char ch : message) {
            cout << ch << flush;
            this_thread::sleep_for(chrono::milliseconds(delayMs));
        }
        cout << endl;
        resetColor();
    }

    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};


#endif // !STYLE_DECORATOR_H
