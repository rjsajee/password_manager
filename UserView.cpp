#include "UserView.h"
#include <iostream>
#include "Utility.h"
using namespace std;

void UserView::showMainMenu() {
    enableVirtualTerminalProcessing();

    // Box design for Welcome Screen
    cout << Color::Cyan;
    cout << "##############################################" << endl;
    cout << "#                                            #" << endl;
    cout << "#   " << Color::Yellow << Color::Bold << "Welcome to the Password Manager!" << Color::Cyan << "   #" << endl;
    cout << "#                                            #" << endl;
    cout << "##############################################" << Color::Reset << endl;

    // Display Menu Options
    cout << Color::Magenta << "\n1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << Color::Reset << endl;

    cout << Color::Green << "\nEnter your choice: " << Color::Reset;
}

void UserView::displayMessage(const string& message) {
    cout << message << std::endl;
}

string UserView::promptUsername() {
    string username;
    cout << "USERNAME: ";
    cin >> username;
    return username;
}

string UserView::promptPassword() {
    string password;
    cout << "PASSWORD: ";
    cin >> password;
    return password;
}

string UserView::promptRole() {
    string role;
    cout << "ROLE (admin/user): ";
    cin >> role;
    return role;
}
