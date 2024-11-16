#ifndef PROFILE_VIEW_H
#define PROFILE_VIEW_H

#include "ProfileModel.h"
#include <string>
#include <map>

class ProfileView {
public:
    void showProfileMenu(const std::string& username, const std::string& role);
    void displayPasswords(const std::map<int, PasswordRecord>& passwords);
    void displaySortedPasswords(const std::multimap<std::string, PasswordRecord>& passwords);
    PasswordRecord promptPasswordDetails();
    int promptPasswordId();
    void displayMessage(const std::string& message);

private:
    AppType promptAppType();
};

#endif
