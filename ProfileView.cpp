#include "ProfileView.h"
#include <iostream>

using namespace std;

void ProfileView::showProfileMenu(const string& username) {
    cout << "\n--- Profile Screen ---" << endl;
    cout << "Welcome, " << username << "!" << endl;
    cout << "1. View All passwords" << endl;
    cout << "2. Add Password" << endl;
    cout << "3. Edit Password" << endl;
    cout << "4. Delete Password" << endl;
    cout << "5. Logout" << endl;
}

void ProfileView::displayPasswords(const vector<PasswordRecord>& passwords) {
    cout << "\n--- Stored Passwords ---" << endl;
    for (const auto& record : passwords) {
        cout << "ID: " << record.id << ", Type: ";
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
    cout << "Enter Password: ";
    cin >> record.password;

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
