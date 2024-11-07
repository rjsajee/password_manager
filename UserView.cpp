#include "UserView.h"
#include <iostream>
using namespace std;

void UserView::showMainMenu() {
    cout << "\t\t\t Welcome to the Password Manager App\n\n";
    cout << "\t\t| Press 1 to Register           |\n";
    cout << "\t\t| Press 2 to Login              |\n";
    cout << "\t\t| Press 3 to Exit               |\n";
    cout << "Enter your choice: ";
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
