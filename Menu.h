#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include "User.h"
using namespace std;

/***********************************************************************
 * FUNCTION - displayMainMenu
 * ---------------------------------------------------------------------
 * Displays the main menu. This is the default selection menu for users
 * who are not logged in yet.
 *
 * EXAMPLE OUTPUT (console):
 * 		===============================================================
 * 		SMART CAMPUS RESERVATION SYSTEM
 * 		---------------------------------------------------------------
 *		What would you like to do today?
 * 		0. Exit program
 * 		1. Create an account
 * 		2. Login to your account
 * 		3. Reserve campus resources
 * 		===============================================================
 *
 * ---------------------------------------------------------------------
 * Returns nothing; outputs main menu.
 **********************************************************************/
void displayMainMenu();

/***********************************************************************
 * FUNCTION - displayUserMenu
 * ---------------------------------------------------------------------
 * Displays a menu for users who are logged in. This becomes the default
 * selection menu for users who are logged in.
 *
 * EXAMPLE OUTPUT (console):
 * 		===============================================================
 * 		SMART CAMPUS RESERVATION SYSTEM | STUDENT username
 * 		---------------------------------------------------------------
 * 		What would you like to do today?
 * 		0. Logout
 * 		1. Reserve campus resources
 * 		===============================================================
 *
 * ---------------------------------------------------------------------
 * Returns nothing; outputs menu for users who are logged in
 **********************************************************************/
void displayAdminMenu(User& u);


void getAndValidateMenuInput(int& input);


void createUser(string userName, string role);
void createAccount(const int BORDER_SIZE, User& user);


/***********************************************************************
 * FUNCTION - validateUsername
 * ---------------------------------------------------------------------
 * Takes a user's role and username and searches through the respective
 * file. Prompts for a new username until a unique username is chosen.
 * ---------------------------------------------------------------------
 * Returns a string representing the unique username chosen by the user.
 **********************************************************************/
void addUserToFile(ostream& outFile, User& u);


#endif
