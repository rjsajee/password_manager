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

    string randomPassword = model.generateRandomPassword();
    view.displayMessage("Generated Password: " + randomPassword);
    view.displayMessage("Do you want to use this generated password? (yes/no)");

    string choice;
    cin >> choice;
    string password;

    if (choice == "yes") {
        password = randomPassword;
    }
    else {
        password = view.promptPassword();
    }

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

        // Instantiate Profile components and start profile management
        ProfileModel profileModel(username);
        ProfileView profileView;
        ProfileController profileController(profileModel, profileView);

        profileController.manageProfile();  // Calls the profile menu after successful login
    }
    else {
        view.displayMessage("Login Error. Please check your username and password.");
    }
}
