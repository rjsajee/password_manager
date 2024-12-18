#include "UserModel.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>        // Use OpenSSL's EVP API
#include <iomanip>
#include <sstream>
#include <ctime>
#include <random>   
using namespace std;

bool UserModel::registerUser(const string& username, const string& password, const string& role) {
    ofstream f1("user_records.txt", ios::app);
    if (f1.is_open()) {
        string hashedPassword = hashPassword(password);  // Hash the password
        string roleCode = (role == "admin") ? "1" : "2"; // Role-based assignment
        f1 << username << ' ' << hashedPassword << ' ' << roleCode << endl;
        f1.close();
        return true;
    }
    else {
        cerr << "Error opening file for writing!" << endl;
        return false;
    }
}

string UserModel::getUserRole(const std::string& username) const {
    ifstream input("user_records.txt");
    string fileUser, filePass, fileRole;

    while (input >> fileUser >> filePass >> fileRole) {
        if (fileUser == username) {
            return (fileRole == "1") ? "admin" : "user";
        }
    }
    return "user";  // Default to user if not found
}

bool UserModel::loginUser(const string& username, const string& password) {
    ifstream input("user_records.txt");
    string fileUser, filePass, fileRole;

    if (!input.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string hashedPassword = hashPassword(password);

    while (input >> fileUser >> filePass >> fileRole) {  // Adjusted for role
        if (fileUser == username && filePass == hashedPassword) {
            cout << "User role: " << ((fileRole == "1") ? "admin" : "user") << endl; // Optional display
            return true;
        }
    }
    return false;
}

string UserModel::generateRandomPassword(int length) {
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

string UserModel::hashPassword(const string& password) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        cerr << "Error creating context" << endl;
        return "";
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        cerr << "Error initializing digest" << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    if (EVP_DigestUpdate(context, password.c_str(), password.size()) != 1) {
        cerr << "Error updating digest" << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length;
    if (EVP_DigestFinal_ex(context, hash, &hash_length) != 1) {
        cerr << "Error finalizing digest" << endl;
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
