#ifndef I_AUTH_CONSOLE_H
#define I_AUTH_CONSOLE_H

class IAuthConsole {
public:
    virtual void displayTerminal() = 0;
    virtual ~IAuthConsole() = default;
};

#endif // I_AUTH_CONSOLE_H
