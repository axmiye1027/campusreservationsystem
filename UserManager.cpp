/******************************************************************************
 * AUTHORS			: Paul S, Ryland L, Amy X, Cristal D, Elizabeth S
 * PROJECT #3		: Campus Reservation System
 * CLASS			: CS 1C
 * SECTION			: TTh 8a
 * DUE DATE			: 12/22/25
******************************************************************************/
#include "UserManager.h"

/******************************************************************************
 * FUNCTION - isValidUsername
 * ------------------------------------------------------------------------
 * A valid username is one that already exists.
 * ------------------------------------------------------------------------
 * Returns true if the username exists, false otherwise.
******************************************************************************/
bool UserManager::isValidUsername(string username)
{
	string tempUsername;
	string tempRole;
	bool isValid;

	isValid = false;

	ifstream fin(USERNAME_FILE);
	if (!fin.is_open())
	{
		ofstream create(USERNAME_FILE);
		create.close();
		fin.open(USERNAME_FILE);
	}

	//for file reading, don't use a flag. it should be controlled by stream success.
	//automatically terminates at the end of file.
	while (getline(fin, tempUsername) && getline(fin, tempRole))
	{
		if (username == tempUsername)
		{
			username = tempUsername;
			isValid = true;
		}
	}
	return isValid;
}

/**************************************************************************
 * FUNCTION - getsAndValidatesUsername
 * ------------------------------------------------------------------------
 * Prompts for a username until the username is correct.
 * ------------------------------------------------------------------------
 * Returns nothing; outputs command for the user to enter a username.
 *************************************************************************/
void UserManager::getAndValidateUsername(string& username, const string& ERROR_MSG)
{
	bool invalid = true;
	string input;

	do
	{
		cout << "Enter username: ";
		getline(cin, input);
		if (!isValidUsername(input)) //if the username already exists in the file
		{
			invalid = false;        //then the username is invalid, because we want the user to input an original username
		}
		else
		{
			cout << ERROR_MSG;
		}
	} while (invalid);

	username = input;
}


/**************************************************************************
 * FUNCTION - login
 * ------------------------------------------------------------------------
 * Prompts users to login.
 * ------------------------------------------------------------------------
 * Returns true if login is successful, false otherwise.
 *************************************************************************/
bool UserManager::login(const int BORDER_SIZE, User& user)
{
	string username;
	string role;

	cout << left;
	cout << endl;
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << "LOGIN\n";
	cout << setfill('-') << setw(BORDER_SIZE) << "" << endl;


	cout << "Enter a username: ";
	getline(cin, username);

	if (isValidUsername(username))
	{
		user.setIsLoggedIn(true);
		user.setUsername(username);
		user.setRole(getRoleFromUsername(username));
		cout << "Login successsful!\n";
	}
	else
	{
		cout << "Login failed.\n";
	}

	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << endl;
	cout << right;


	return user.getIsLoggedIn(); //true if the user exists

}

User UserManager::createAccount(const int BORDER_SIZE)
{
	string username;
	char roleCh;
	string role;
	string ERROR_MSG = "Please choose another username.\n";

	cout << left;
	cout << endl;
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

	getAndValidateUsername(username, ERROR_MSG);

	User user(username, role);
	user.setIsLoggedIn(true);

	addUserToFile(user);

	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << endl;
	cout << right;

	return user;
}


void UserManager::addUserToFile(User& user)
{
	ofstream fout(USERNAME_FILE, ios::app);

	fout << user.getUsername() << endl << user.getRole() << endl;

	cout << "An account for " << user.getUsername()
		 << " (" << user.getRole() << ") has been created!\n";

	fout.close();
}

string UserManager::getRoleFromUsername(string username)
{
	string tempUsername;
	string tempRole;
	string role;

	role = "User does not exist.\n";

	ifstream fin(USERNAME_FILE);
	if (!fin.is_open())
	{
		ofstream create(USERNAME_FILE);
		create.close();
		fin.open(USERNAME_FILE);
	}

	//for file reading, don't use a flag. it should be controlled by stream success.
	//automatically terminates at the end of file.
	while (getline(fin, tempUsername) && getline(fin, tempRole))
	{
		if (username == tempUsername)
		{
			role = tempRole;
		}
	}

	return role;

}
