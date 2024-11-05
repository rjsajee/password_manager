#ifndef PROFILE_CONTROLLER_H
#define PROFILE_CONTROLLER_H

#include "ProfileModel.h"
#include "ProfileView.h"
#include <string>

class ProfileController {
public:
    ProfileController(ProfileModel& model, ProfileView& view);
    void manageProfile();

private:
    ProfileModel& model;
    ProfileView& view;

    void viewAllPasswords();
    void addPassword();
    void editPassword();
    void deletePassword();
};

#endif
