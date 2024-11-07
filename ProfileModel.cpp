#include "ProfileModel.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

ProfileModel::ProfileModel(const string& username) : username(username), nextId(1) {
    loadPasswords();
}

bool ProfileModel::addPassword(const PasswordRecord& record) {
    passwords.push_back(record);
    savePasswords();
    return true;
}

bool ProfileModel::editPassword(int id, const PasswordRecord& updatedRecord) {
    for (auto& record : passwords) {
        if (record.id == id) {
            record = updatedRecord;
            savePasswords();
            return true;
        }
    }
    return false;
}

bool ProfileModel::deletePassword(int id) {
    auto it = remove_if(passwords.begin(), passwords.end(), [id](const PasswordRecord& record) {
        return record.id == id;
        });
    if (it != passwords.end()) {
        passwords.erase(it, passwords.end());
        savePasswords();
        return true;
    }
    return false;
}

vector<PasswordRecord> ProfileModel::getAllPasswords() const {
    return passwords;
}

vector<PasswordRecord> ProfileModel::getUserPasswords() const {
    vector<PasswordRecord> userPasswords;
    for (const auto& record : passwords) {
        if (record.username == username) {
            userPasswords.push_back(record);
        }
    }
    return userPasswords;
}

string ProfileModel::getUsername() const {
    return username;
}

void ProfileModel::loadPasswords() {
    ifstream file("user_profiles.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        PasswordRecord record;
        int appTypeInt;
        iss >> record.id >> appTypeInt >> record.username >> record.password >> record.appName;
        record.appType = static_cast<AppType>(appTypeInt);
        if (record.appType == AppType::Website || record.appType == AppType::Game) {
            iss >> record.extraInfo;
        }
        iss >> record.dateCreated >> record.dateLastUpdated;
        if (iss && username == this->username) {
            passwords.push_back(record);
            nextId = max(nextId, record.id + 1);
        }
    }
}

void ProfileModel::savePasswords() const {
    ofstream file("user_profiles.txt", ios::trunc);
    for (const auto& record : passwords) {
        file << record.id << " " << static_cast<int>(record.appType) << " " << record.username << " "
            << record.password << " " << record.appName << " ";
        if (record.appType == AppType::Website || record.appType == AppType::Game) {
            file << record.extraInfo << " ";
        }
        file << record.dateCreated << " " << record.dateLastUpdated << "\n";
    }
}

string ProfileModel::getCurrentDate() {
    time_t now = time(0);
    tm timeStruct;

#ifdef _WIN32
    localtime_s(&timeStruct, &now);
#else
    localtime_r(&now, &timeStruct);
#endif

    stringstream date;
    date << (1900 + timeStruct.tm_year) << "-"
        << setw(2) << setfill('0') << (1 + timeStruct.tm_mon) << "-"
        << setw(2) << setfill('0') << timeStruct.tm_mday;

    return date.str();
}
