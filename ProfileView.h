#ifndef PROFILE_VIEW_H
#define PROFILE_VIEW_H

#include "ProfileModel.h"
#include <string>
#include <vector>

class ProfileView {
public:
    void showProfileMenu(const std::string& username);
    void displayPasswords(const std::vector<PasswordRecord>& passwords);
    PasswordRecord promptPasswordDetails();
    int promptPasswordId();
    void displayMessage(const std::string& message);

private:
    AppType promptAppType();
};

#endif
