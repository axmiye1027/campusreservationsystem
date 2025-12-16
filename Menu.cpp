#include "Menu.h"

/***********************************************************************
 * FUNCTION - displayMainMenu
 * ---------------------------------------------------------------------
 * Displays the main menu.
 *
 * ---------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 *
 * ---------------------------------------------------------------------
 * Returns nothing, outputs the main menu.
 **********************************************************************/
void displayMainMenu()
{
	const int BORDER_SIZE = 50;
	cout << left;
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << "SMART CAMPUS RESERVATION SYSTEM\n";
	cout << setfill('-') << setw(BORDER_SIZE) << "" << endl;
	cout << "What would you like to do today?\n";
	cout << "0. Exit Program\n1. Create an account\n2. Login to your account\n"
			"3. Reserve campus resources\n";
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << right;
}

/***********************************************************************
 * FUNCTION - displayUserMenu
 * ---------------------------------------------------------------------
 * Displays a menu for users who are logged in. This becomes the default
 * selection menu for users who are logged in.
 *
 * ---------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			u		: a reference to a user
 * ---------------------------------------------------------------------
 * Returns nothing; outputs menu for users who are logged in
 **********************************************************************/
void displayUserMenu(User& u)
{
	const int BORDER_SIZE = 50;

	if (u.getRole() != "Student" ||
		u.getRole() != "Admin")
	{
		return;
	}

	cout << left;
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << "SMART CAMPUS RESERVATION SYSTEM | " << u.getRole() << ": "
		 << u.getUsername() << endl;
	cout << setfill('-') << setw(BORDER_SIZE) << "" << endl;
	cout << "What would you like to do today?\n";
	cout << "0. Exit Program\n1. Reserve campus resources\n";
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << right;

}


void getAndValidateMenuInput(int& input)
{
	bool invalid = true;

	do
	{
		cout << "Enter selection: ";
		cin >> input;
		cin.ignore(10000, '\n');

		if (input < 0 || input > 3)
		{
			cout << "Invalid entry. Try again.\n";
		}
		else
		{
			invalid = false;
		}
	} while (invalid);
}



//Helper functions

void addUserToFile(User& user)
{
	ofstream fout;


	cout << "An account for " << user.getUsername()
		 << "(" << user.getRole() << ") has been created!\n";

	if (user.getRole() == "Admin")
	{
		fout.open("admin_usernames.txt", ios::app);
	}
	else if (user.getRole() == "Student")
	{
		fout.open("student_usernames.txt", ios::app);
	}

	fout << user.getUsername() << endl;
	fout.close();
}

//should update a user, otherwise we can't use the user functions/class
//for login and whatnot
void createAccount(const int BORDER_SIZE, User& user)
{
	string userName;
	char roleCh;
	string role;

	cout << left;
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << "CREATING ACCOUNT\n";
	cout << setfill('-') << setw(BORDER_SIZE) << "" << endl;

	cout << "Choose role (a/s): ";
	cin.get(roleCh);
	cin.ignore(10000, '\n');
	switch(roleCh)
	{
		case 'a': role = "Admin"; break;
		case 's': role = "Student"; break;
	}

	cout << "Enter username: ";
	getline(cin, userName);
	userName = validateUsername(userName, role);

	user.setRole(role);
	user.setUsername(userName);

	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << right;
}








