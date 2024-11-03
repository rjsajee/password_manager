// UserModel.h
#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <string>
using namespace std;

class UserModel {
public:
    bool registerUser(const string& username, const string& password);
    bool loginUser(const string& username, const string& password);
    string generateRandomPassword(int length = 12);

private:
    string hashPassword(const std::string& password); 
};


#endif
#pragma once
