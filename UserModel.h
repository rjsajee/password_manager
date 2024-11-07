#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <string>
using namespace std;

class UserModel {
public:
    bool registerUser(const string& username, const string& password, const string& role);
    bool loginUser(const string& username, const string& password);
    string generateRandomPassword(int length = 12);
    string getUserRole(const std::string& username) const;


private:
    string hashPassword(const string& password);
};

#endif
