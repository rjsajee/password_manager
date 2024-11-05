#include "ProfileController.h"
#include <iostream>

using namespace std;

ProfileController::ProfileController(ProfileModel& model, ProfileView& view)
    : model(model), view(view) {}

void ProfileController::manageProfile() {
    int choice;
    do {
        view.showProfileMenu(model.getUsername());
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: viewAllPasswords(); break;
        case 2: addPassword(); break;
        case 3: editPassword(); break;
        case 4: deletePassword(); break;
        case 5: view.displayMessage("Logging out..."); break;
        default: view.displayMessage("Invalid choice. Try again.");
        }
    } while (choice != 5);
}

void ProfileController::viewAllPasswords() {
    view.displayPasswords(model.getAllPasswords());
}

void ProfileController::addPassword() {
    PasswordRecord newRecord = view.promptPasswordDetails();
    if (model.addPassword(newRecord)) {
        view.displayMessage("Password added successfully!");
    }
    else {
        view.displayMessage("Failed to add password.");
    }
}

void ProfileController::editPassword() {
    int id = view.promptPasswordId();
    PasswordRecord updatedRecord = view.promptPasswordDetails();
    if (model.editPassword(id, updatedRecord)) {
        view.displayMessage("Password updated successfully!");
    }
    else {
        view.displayMessage("Failed to update password.");
    }
}

void ProfileController::deletePassword() {
    int id = view.promptPasswordId();
    if (model.deletePassword(id)) {
        view.displayMessage("Password deleted successfully!");
    }
    else {
        view.displayMessage("Failed to delete password.");
    }
}
