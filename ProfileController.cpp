#include "ProfileController.h"
#include <iostream>

using namespace std;

ProfileController::ProfileController(ProfileModel& model, ProfileView& view, const string& role)
    : model(model), view(view), role(role) {}

void ProfileController::manageProfile() {
    int choice;
    do {
        view.showProfileMenu(model.getUsername(), role);
        cout << "Choose an option: ";
        cin >> choice;

        if (role == "admin") {
            switch (choice) {
            case 1: viewAllPasswords(); break;
            case 2: editPassword(); break;
            case 3: deletePassword(); break;
            case 4: view.displayMessage("Logging out..."); break;
            default: view.displayMessage("Invalid choice. Try again.");
            }
        }
        else {
            switch (choice) {
            case 1: viewAllPasswords(); break;
            case 2: addPassword(); break;
            case 3: view.displayMessage("Logging out..."); break;
            default: view.displayMessage("Invalid choice. Try again.");
            }
        }
    } while (role == "admin" ? choice != 4 : choice != 3);
}

void ProfileController::viewAllPasswords() {
    auto records = (role == "admin") ? model.getAllPasswords() : model.getUserPasswords();
    //view.displayPasswords(records);
}

void ProfileController::addPassword() {
    if (role == "user") {
        PasswordRecord newRecord = view.promptPasswordDetails();

        // Generate and display a random password
        std::string randomPassword = model.generateRandomPassword();
        view.displayMessage("Generated Password: " + randomPassword);
        view.displayMessage("Do you want to use this generated password? (yes/no)");

        std::string choice;
        std::cin >> choice;

        if (choice == "yes") {
            newRecord.password = randomPassword;
        }
        else {
            // Prompt the user to manually enter a password
            view.displayMessage("Please enter your password:");
            std::cin >> newRecord.password;
        }

        newRecord.password = model.hashPassword(newRecord.password);  // Hash the password before storing

        if (model.addPassword(newRecord)) {
            view.displayMessage("Password added successfully!");
        }
        else {
            view.displayMessage("Failed to add password.");
        }
    }
    else {
        view.displayMessage("Admins cannot add passwords.");
    }
}


void ProfileController::editPassword() {
    if (role == "admin") {
        int id = view.promptPasswordId();
        PasswordRecord updatedRecord = view.promptPasswordDetails();
        if (model.editPassword(id, updatedRecord)) {
            view.displayMessage("Password updated successfully!");
        }
        else {
            view.displayMessage("Failed to update password.");
        }
    }
    else {
        view.displayMessage("Users cannot edit passwords.");
    }
}

void ProfileController::deletePassword() {
    if (role == "admin") {
        int id = view.promptPasswordId();
        if (model.deletePassword(id)) {
            view.displayMessage("Password deleted successfully!");
        }
        else {
            view.displayMessage("Failed to delete password.");
        }
    }
    else {
        view.displayMessage("Users cannot delete passwords.");
    }
}
