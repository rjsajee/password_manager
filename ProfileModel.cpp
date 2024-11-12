#include "ProfileModel.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <openssl/evp.h>
#include <random>
#include <iostream>

using namespace std;

ProfileModel::ProfileModel(const string& username) : username(username), nextId(1) {
    loadPasswords();
}

bool ProfileModel::addPassword(const PasswordRecord& record) {
    PasswordRecord newRecord = record;
    newRecord.id = nextId++;
    newRecord.password = hashPassword(record.password);  // Hash password before storing
    passwords[newRecord.id] = newRecord;
    savePasswords();
    return true;
}

bool ProfileModel::editPassword(int id, const PasswordRecord& updatedRecord) {
    if (passwords.find(id) != passwords.end()) {
        PasswordRecord newRecord = updatedRecord;
        newRecord.password = hashPassword(updatedRecord.password);  // Hash updated password
        passwords[id] = newRecord;
        savePasswords();
        return true;
    }
    return false;
}

bool ProfileModel::deletePassword(int id) {
    if (passwords.erase(id)) {
        savePasswords();
        return true;
    }
    return false;
}

map<int, PasswordRecord> ProfileModel::getAllPasswords() const {
    return passwords;
}

map<int, PasswordRecord> ProfileModel::getUserPasswords() const {
    map<int, PasswordRecord> userPasswords;
    for (const std::pair<const int, PasswordRecord>& entry : passwords) {
        const PasswordRecord& record = entry.second;
        if (record.username == username) {
            userPasswords[entry.first] = record;
        }
    }
    return userPasswords;
}

string ProfileModel::getUsername() const {
    return username;
}

void ProfileModel::loadPasswords() {
    ifstream file("user_profiles.txt");
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        PasswordRecord record;
        string appTypeStr;

        if (!(iss >> record.id >> appTypeStr >> record.username >> record.password >> record.appName)) {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }

        record.appType = stringToAppType(appTypeStr);

        if (record.appType == AppType::Website || record.appType == AppType::Game) {
            iss >> record.extraInfo;
        }

        iss >> record.dateCreated >> record.dateLastUpdated;

        passwords[record.id] = record;
        nextId = max(nextId, record.id + 1);
    }
}

void ProfileModel::savePasswords() const {
    ofstream file("user_profiles.txt", ios::trunc);
    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const std::pair<const int, PasswordRecord>& entry : passwords) {
        const PasswordRecord& record = entry.second;

        file << record.id << " " << appTypeToString(record.appType) << " "
            << record.username << " " << record.password << " "
            << record.appName << " ";

        if (record.appType == AppType::Website || record.appType == AppType::Game) {
            file << record.extraInfo << " ";
        }

        file << record.dateCreated << " " << record.dateLastUpdated << "\n";
    }
}

string ProfileModel::generateRandomPassword(int length) {
    const string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()";
    string password;
    mt19937 generator(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<> distribution(0, chars.size() - 1);

    for (int i = 0; i < length; ++i) {
        password += chars[distribution(generator)];
    }
    return password;
}

string ProfileModel::hashPassword(const string& password) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        cerr << "Error creating hash context." << endl;
        return "";
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        cerr << "Error initializing digest." << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    if (EVP_DigestUpdate(context, password.c_str(), password.size()) != 1) {
        cerr << "Error updating digest." << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length;

    if (EVP_DigestFinal_ex(context, hash, &hash_length) != 1) {
        cerr << "Error finalizing digest." << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    EVP_MD_CTX_free(context);

    stringstream ss;
    for (unsigned int i = 0; i < hash_length; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
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

std::string ProfileModel::appTypeToString(AppType type) {
    switch (type) {
    case AppType::Website: return "Website";
    case AppType::DesktopApplication: return "DesktopApplication";
    case AppType::Game: return "Game";
    default: return "Unknown";
    }
}

AppType ProfileModel::stringToAppType(const std::string& typeStr) {
    if (typeStr == "Website") return AppType::Website;
    if (typeStr == "DesktopApplication") return AppType::DesktopApplication;
    if (typeStr == "Game") return AppType::Game;
    return AppType::Website; // Default to Website if unknown
}
