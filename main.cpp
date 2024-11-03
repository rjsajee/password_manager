// main.cpp
#include "UserModel.h"
#include "UserView.h"
#include "UserController.h"
using namespace std;

int main() {
    UserModel model;
    UserView view;
    UserController controller(model, view);
    controller.start();
    return 0;
}
