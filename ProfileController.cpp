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
            case 3: searchPasswordByAppName(); break;
            case 4: view.displayMessage("Logging out..."); break;
            default: view.displayMessage("Invalid choice. Try again.");
            }
        }
    } while (role == "admin" ? choice != 4 : choice != 4);
}

void ProfileController::viewAllPasswords() {
    if (role == "admin") {
        auto records = model.getAllPasswords();
        view.displayPasswords(records);
    }
    else {
        view.displayMessage("View your passwords:\n1. Normal view\n2. Filter by Last Updated Date");
        int sortChoice;
        cin >> sortChoice;

        if (sortChoice == 2) {
            view.displayMessage("Enter the Last Updated Date (YYYY-MM-DD):");
            string enteredDate;
            cin >> enteredDate;

            auto filteredRecords = model.getPasswordsByLastUpdatedDate(enteredDate);
            if (filteredRecords.empty()) {
                view.displayMessage("No passwords found for the entered date.");
            }
            else {
                view.displaySortedPasswords(filteredRecords);
            }
        }
        else {
            auto records = model.getUserPasswords();
            view.displayPasswords(records);
        }
    }
}

void ProfileController::addPassword() {
    if (role == "user") {
        PasswordRecord newRecord = view.promptPasswordDetails();

        newRecord.creatorUsername = model.getUsername();
        newRecord.dateCreated = newRecord.dateLastUpdated = ProfileModel::getCurrentDate();

        string randomPassword = model.generateRandomPassword();
        view.displayMessage("Generated Password: " + randomPassword);
        view.displayMessage("Do you want to use this generated password? (yes/no)");

        string choice;
        cin >> choice;

        if (choice == "yes") {
            newRecord.password = randomPassword;
        }
        else {
            view.displayMessage("Please enter your password:");
            cin >> newRecord.password;
        }

        newRecord.password = model.hashPassword(newRecord.password);

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

void ProfileController::searchPasswordByAppName() {
    if (role == "admin") {
        view.displayMessage("Admins cannot search passwords.");
        return;
    }

    view.displayMessage("Enter the App or Game Name to search:");
    string searchQuery;
    cin.ignore();
    getline(cin, searchQuery);

    map<int, PasswordRecord> userPasswords = model.getUserPasswords();
    map<int, PasswordRecord> searchResults;

    for (const auto& entry : userPasswords) {
        const PasswordRecord& record = entry.second;
        if (record.appName.find(searchQuery) != string::npos) {
            searchResults[entry.first] = record;
        }
    }

    if (searchResults.empty()) {
        view.displayMessage("No records found matching the search query.");
    }
    else {
        view.displayPasswords(searchResults);
    }
}
