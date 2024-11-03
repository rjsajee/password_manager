// UserView.h
#ifndef USER_VIEW_H
#define USER_VIEW_H

#include <string>
using namespace std;

class UserView {
public:
    void showMainMenu();
    void displayMessage(const string& message);
    string promptUsername();
    string promptPassword();
};

#endif
