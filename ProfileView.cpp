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
        cout << "3. Search by App/Game Name" << endl;
        cout << "4. Logout" << endl;
    }
}

void ProfileView::displayPasswords(const map<int, PasswordRecord>& passwords) {
    cout << "\n--- Stored Passwords ---" << endl;
    for (const auto& entry : passwords) {
        const int& id = entry.first;
        const PasswordRecord& record = entry.second;

        cout << "ID: " << id << ", Type: ";
        switch (record.appType) {
        case AppType::Website: cout << "Website"; break;
        case AppType::DesktopApplication: cout << "Desktop Application"; break;
        case AppType::Game: cout << "Game"; break;
        default: cout << "Unknown"; break;
        }

        cout << ", Creator Username: " << record.creatorUsername
            << ", App Username: " << record.appUsername
            << ", App Name: " << record.appName;

        if (!record.extraInfo.empty()) {
            cout << ", Extra Info: " << record.extraInfo;
        }

        cout << ", Date Created: " << record.dateCreated
            << ", Last Updated: " << record.dateLastUpdated << endl;
    }
}

void ProfileView::displaySortedPasswords(const multimap<string, PasswordRecord>& passwords) {
    cout << "\n--- Your Passwords (Filtered by Last Updated Date) ---" << endl;
    for (const auto& entry : passwords) {
        const PasswordRecord& record = entry.second;
        cout << "ID: " << record.id << ", Type: ";
        switch (record.appType) {
        case AppType::Website: cout << "Website"; break;
        case AppType::DesktopApplication: cout << "Desktop Application"; break;
        case AppType::Game: cout << "Game"; break;
        default: cout << "Unknown"; break;
        }

        cout << ", Creator Username: " << record.creatorUsername
            << ", App Username: " << record.appUsername
            << ", App Name: " << record.appName;

        if (!record.extraInfo.empty()) {
            cout << ", Extra Info: " << record.extraInfo;
        }

        cout << ", Date Created: " << record.dateCreated
            << ", Last Updated: " << record.dateLastUpdated << endl;
    }
}

PasswordRecord ProfileView::promptPasswordDetails() {
    PasswordRecord record;
    record.appType = promptAppType();

    cout << "Enter App Username: ";
    cin >> record.appUsername;

    cout << "Enter App Name: ";
    cin >> record.appName;

    switch (record.appType) {
    case AppType::Website:
        cout << "Enter Website URL: ";
        cin >> record.extraInfo;
        break;
    case AppType::Game:
        cout << "Enter Game Developer: ";
        cin >> record.extraInfo;
        break;
    default:
        record.extraInfo = "";
        break;
    }

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

    switch (type) {
    case 1: return AppType::Website;
    case 2: return AppType::DesktopApplication;
    case 3: return AppType::Game;
    default:
        cout << "Invalid type selected, defaulting to Website." << endl;
        return AppType::Website;
    }
}
