// UserController.cpp
#include "UserController.h"
#include <iostream>
using namespace std;

UserController::UserController(UserModel& model, UserView& view)
    : model(model), view(view) {}

void UserController::start() {
    int choice;
    do {
        view.showMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            handleRegister();
            break;
        case 2:
            handleLogin();
            break;
        case 3:
            view.displayMessage("Exiting the application.");
            break;
        default:
            view.displayMessage("Please select a valid option.");
            break;
        }
    } while (choice != 3);
}

void UserController::handleRegister() {
    string username = view.promptUsername();
    string password = view.promptPassword();

    if (model.registerUser(username, password)) {
        view.displayMessage("Registration is successful!");
    }
    else {
        view.displayMessage("Registration failed!");
    }
}

void UserController::handleLogin() {
    string username = view.promptUsername();
    string password = view.promptPassword();

    if (model.loginUser(username, password)) {
        view.displayMessage("Your login is successful! Thanks for logging in.");
    }
    else {
        view.displayMessage("Login Error. Please check your username and password.");
    }
}
