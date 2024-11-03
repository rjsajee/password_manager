// UserModel.cpp
#include "UserModel.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>        // Use OpenSSL's EVP API
#include <iomanip>
#include <sstream>
#include <ctime>
#include <random>   
using namespace std;

bool UserModel::registerUser(const string& username, const string& password) {
    ofstream f1("user_records.txt", ios::app);
    if (f1.is_open()) {
        string hashedPassword = hashPassword(password);  // Hash the password
        f1 << username << ' ' << hashedPassword << endl;
        f1.close();
        return true;
    }
    else {
        cerr << "Error opening file for writing!" << endl;
        return false;
    }
}

bool UserModel::loginUser(const string& username, const string& password) {
    ifstream input("user_records.txt");
    string fileUser, filePass;

    if (!input.is_open()) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string hashedPassword = hashPassword(password);

    while (input >> fileUser >> filePass) {
        if (fileUser == username && filePass == hashedPassword) {
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

// Updated function to hash passwords using the EVP API
string UserModel::hashPassword(const string& password) {
    // Create a context for hashing
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        cerr << "Error creating context" << endl;
        return "";
    }

    // Initialize the context with SHA-256
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        cerr << "Error initializing digest" << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    // Update the context with the password data
    if (EVP_DigestUpdate(context, password.c_str(), password.size()) != 1) {
        cerr << "Error updating digest" << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    // Finalize the digest and retrieve the hashed output
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length;
    if (EVP_DigestFinal_ex(context, hash, &hash_length) != 1) {
        cerr << "Error finalizing digest" << endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    // Free the context
    EVP_MD_CTX_free(context);

    // Convert the hash to a hexadecimal string
    stringstream ss;
    for (unsigned int i = 0; i < hash_length; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();  // Return the hashed password as a hexadecimal string
}
