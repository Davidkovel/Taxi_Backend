#ifndef I_MENU_H
#define I_MENU_H

template <typename TDTO>
class IMenu {
public:
    virtual void displayMenu(TDTO& dto) = 0;
    virtual ~IMenu() = default;
};


#endif // !I_MENU_H
