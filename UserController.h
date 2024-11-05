#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "UserModel.h"
#include "UserView.h"
#include "ProfileController.h"
#include "ProfileModel.h"
#include "ProfileView.h"

class UserController {
public:
    UserController(UserModel& model, UserView& view);
    void start();

private:
    UserModel& model;
    UserView& view;

    void handleRegister();
    void handleLogin();
};

#endif
