/******************************************************************************
 * AUTHORS			: Paul S, Ryland L, Amy X, Cristal D, Elizabeth S
 * PROJECT #3		: Campus Reservation System
 * CLASS			: CS 1C
 * SECTION			: TTh 8a
 * DUE DATE			: 12/22/25
******************************************************************************/

#ifndef USERMANAGER_H_
#define USERMANAGER_H_

#include "User.h"
#include <iomanip>

/******************************************************************************
 * CLASS - UserManager
 * ----------------------------------------------------------------------------
 * UserManager is responsible for managing all user-related operations that
 * exist outside the lifetime of a single User object. It handles tasks such as
 * creating accounts, validating usernames, authenticating logins, determining
 * user roles, and loading or saving user data to persistent storage.
******************************************************************************/
class UserManager
{
private:
	const string USERNAME_FILE = "usernames.txt";

public:
	/**************************************************************************
	 * FUNCTION - login
	 * ------------------------------------------------------------------------
	 * Prompts the user for their username. Checks if username is an existing
	 * user; if it is, login will be successful.
	 *
	 * EXAMPLE OUTPUT (console):
	 * 	============================================
	 * 	LOGIN
	 * 	--------------------------------------------
	 * 	Enter username: JohnDoe123
	 * 	Login successful!
	 * 	============================================
	 *
	 * ------------------------------------------------------------------------
	 * Returns nothing, outputs login interface and validates user.
	 *************************************************************************/
	bool login(const int BORDER_SIZE, User& user);

	/**************************************************************************
	 * FUNCTION - createAccount
	 * ------------------------------------------------------------------------
	 * Provides an interface for the user to login. Validates username.
	 * Assigns username and role to the User object user. Does not validate
	 * role.
	 *
	 * EXAMPLE OUTPUT (console):
	 * 	============================================
	 * 	CREATE ACCOUNT
	 * 	--------------------------------------------
	 * 	Enter username: JohnDoe123
	 * 	Please choose another username.
	 * 	Enter username: JohnDoe
	 * 	Choose role (a/s): a
	 * 	Account successfully created!
	 * 	============================================
	 *
	 * ------------------------------------------------------------------------
	 * Returns nothing, outputs login interface and validates user.
	 *************************************************************************/
	User createAccount(const int BORDER_SIZE);

	/**************************************************************************
	 * FUNCTION - addUserToFile
	 * ------------------------------------------------------------------------
	 * Writes a user to file. Checks that the username doesn't already exist in
	 * the file.
	 *
	 * EXAMPLE OUTPUT (file):
	 * 	JohnnyDoe123
	 * 	Admin
	 *
	 * ------------------------------------------------------------------------
	 * Returns nothing, writes to a file.
	 *************************************************************************/
	void addUserToFile(User& user);

	/**************************************************************************
	 * FUNCTION - isValidUsername
	 * ------------------------------------------------------------------------
	 * A valid username is one that already exists.
	 * ------------------------------------------------------------------------
	 * Returns true if the username exists, false otherwise.
	 *************************************************************************/

	bool isValidUsername(string username);

	/**************************************************************************
	 * FUNCTION - getsAndValidatesUsername
	 * ------------------------------------------------------------------------
	 * Prompts for a username until the username is correct.
	 * ------------------------------------------------------------------------
	 * Returns nothing; outputs command for the user to enter a username.
	 *************************************************************************/
	void getAndValidateUsername(string& username, const string& ERROR_MSG);


	string getRoleFromUsername(string username);

};

#endif /* USERMANAGER_H_ */
