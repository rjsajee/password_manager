#include "ProfileView.h"
#include <iostream>

using namespace std;

void ProfileView::showProfileMenu(const string& username, const string& role) {
    cout << "\n--- Profile Screen ---" << endl;
    cout << "Welcome, " << username << "!" << endl;

    if (role == "admin") {
        cout << "1. View All Users' Passwords" << endl;
        cout << "2. Edit Password" << endl;
        cout << "3. Delete Password" << endl;
        cout << "4. Logout" << endl;
    }
    else {
        cout << "1. View Your Passwords" << endl;
        cout << "2. Add Password" << endl;
        cout << "3. Logout" << endl;
    }
}

void ProfileView::displayPasswords(const map<int, PasswordRecord>& passwords) {
    cout << "\n--- Stored Passwords ---" << endl;
    for (const std::pair<const int, PasswordRecord>& pair : passwords) {
    const int& id = pair.first;
    const PasswordRecord& record = pair.second;

    cout << "ID: " << id << ", Type: ";
    switch (record.appType) {
    case AppType::Website: cout << "Website"; break;
    case AppType::DesktopApplication: cout << "Desktop Application"; break;
    case AppType::Game: cout << "Game"; break;
    }
    cout << ", Username: " << record.username << ", App Name: " << record.appName;
    if (!record.extraInfo.empty()) {
        cout << ", Extra Info: " << record.extraInfo;
    }
    cout << ", Date Created: " << record.dateCreated << ", Last Updated: " << record.dateLastUpdated << endl;
}

}

PasswordRecord ProfileView::promptPasswordDetails() {
    PasswordRecord record;
    record.appType = promptAppType();
    cout << "Enter Username: ";
    cin >> record.username;

    switch (record.appType) {
    case AppType::Website:
        cout << "Enter Website Name: ";
        cin >> record.appName;
        cout << "Enter Website URL: ";
        cin >> record.extraInfo;
        break;
    case AppType::DesktopApplication:
        cout << "Enter Application Name: ";
        cin >> record.appName;
        break;
    case AppType::Game:
        cout << "Enter Game Name: ";
        cin >> record.appName;
        cout << "Enter Game Developer: ";
        cin >> record.extraInfo;
        break;
    }

    record.dateCreated = record.dateLastUpdated = ProfileModel::getCurrentDate();
    return record;
}

int ProfileView::promptPasswordId() {
    int id;
    cout << "Enter Password ID: ";
    cin >> id;
    return id;
}

void ProfileView::displayMessage(const string& message) {
    cout << message << endl;
}

AppType ProfileView::promptAppType() {
    cout << "Select App Type:\n1. Website\n2. Desktop Application\n3. Game\n";
    int type;
    cin >> type;
    return static_cast<AppType>(type - 1);
}
