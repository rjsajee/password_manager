#include<iostream>
#include<fstream>
#include<string.h>
#include "welcome_screen.h"
//#include "main.cpp"

using namespace std;


void regiserFunction() {
	string ruserName, rpassword, ruName, rpass;
	system("cls");

	cout << "\t\t\t	 Please enter username and password	: " << endl;
	cout << "USERNAME ";
	cin >> ruName;
	cout << "PASSWORD ";
	cin >> rpass;

	ofstream f1("user_records.txt", ios::app);
	if (f1.is_open()) {
		f1 << ruName << ' ' << rpass << endl;
		f1.close();
		system("cls");
		cout << "\n\t\t\t Registration is successful! \n";
	}
	else {
		cout << "Error opening file for writing!" << endl;
	}
}

void loginFunction() {
    int count = 0;  // Initialize count to 0
    string userName, password, fileUser, filePass;

    system("cls");

    cout << "\t\t\t Please enter username and password: " << endl;
    cout << "USERNAME: ";
    cin >> userName;
    cout << "PASSWORD: ";
    cin >> password;

    ifstream input("user_records.txt");

    // Check if the file opened successfully
    if (!input.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Loop through the file and compare each record to the input
    while (input >> fileUser >> filePass) {
        if (fileUser == userName && filePass == password) {
            count = 1;  // Set count to 1 if credentials match
            break;      // Break out of the loop on successful login
        }
    }
    input.close();

    // Check if login was successful
    if (count == 1) {
        system("cls");
        cout << userName << "\nYour login is successful\nThanks for logging in!\n";
    }
    else {
        cout << "\nLogin Error\nPlease check your username and password\n";
    }
}
