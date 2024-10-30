#include<iostream>
#include<fstream>
#include<string.h>
#include "welcome_screen.h"
using namespace std;



int main()
{
	int c;
	cout << "\t\t\t__________________________________________________\n\n\n" ;
	cout << "\t\t\t	 Welcome to the Password Manager App		  \n\n\n";
	cout << "\t\t\t__________________     Menu     ___________________\n\n\n";
	cout << "															\n\n";
	cout << "\t\t| Press 1 to Login			|" << endl;
	cout << "\t\t| Press 2 to Register			|" << endl;
	cout << "\t\t| Press 3 to Exit			|" << endl;
	cout << "\n\t\t\t Press enter your choice : ";

	cin >> c;
	cout << endl;	

	switch (c)
	{
	case 1:
		regiserFunction();
	}
}
