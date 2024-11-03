// UserModel.cpp
#include "UserModel.h"
#include <fstream>
#include <iostream>
using namespace std;

bool UserModel::registerUser(const string& username, const string& password) {
    ofstream f1("user_records.txt", ios::app);
    if (f1.is_open()) {
        f1 << username << ' ' << password << endl;
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

    while (input >> fileUser >> filePass) {
        if (fileUser == username && filePass == password) {
            return true;
        }
    }
    return false;
}
