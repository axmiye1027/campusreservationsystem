/******************************************************************************
 * AUTHORS			: Paul S, Ryland L, Amy X, Cristal D, Elizabeth S
 * PROJECT #3		: Campus Reservation System
 * CLASS			: CS 1C
 * SECTION			: TTh 8a
 * DUE DATE			: 12/22/25
******************************************************************************/
#include "Menu.h"
#include <iomanip>

/******************************************************************************
 * FUNCTION - displayMenu
 * ----------------------------------------------------------------------------
 * Displays a menu for users. The menu displayed depends on whether the user
 * is logged in and if they are a student or admin.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 *
 * 		THE ARGUMENTS FOR THE FOLLOWING PARAMETERS WILL BE MODIFIED.
 * 			Input read in the function will be stored in these parameters &
 * 			returned via the parameters.
 * 				u		: reference to a User object
 * ----------------------------------------------------------------------------
 * Returns nothing; outputs menu for users who are logged in
 *****************************************************************************/
void displayMenu(const int BORDER_SIZE, User &u)
{
	cout << left;
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;


	if (!u.getIsLoggedIn())
	{
		cout << "SMART CAMPUS RESERVATION SYSTEM\n";
		cout << "0. Exit\n"
				"1. Create an account\n"
				"2. Login to your account\n";
	}
	else
	{
		cout << "SMART CAMPUS RESERVATION SYSTEM | " << u.getRole()
			 << ": " << u.getUsername() << endl;

		if (u.getRole() == "Student")
		{
			cout << "0. Logout\n"
					"1. Reserve campus resources\n"
					"2. Find campus resources\n"
					"3. View campus resources\n";
		}
		else
		{
			cout << "0. Logout\n"
					"1. Find campus resources\n"
					"2. View campus resources\n"
					"3. Add campus resources\n"
					"4. Edit campus resources\n"
					"5. Delete campus resources\n";
		}
	}
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << right;
}

/******************************************************************************
 * FUNCTION - getAndValidateMenuInput
 * ----------------------------------------------------------------------------
 * Prompts for initial user input and checks if it within the valid range
 * specified by LOWER_BOUND and UPPER_BOUND.
 *
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 				LOWER_BOUND	: lower bound for integer inputs, not included
 * 				UPPER_BOUND	: upper bound for integer inputs, not included
 *
 * 		THE ARGUMENTS FOR THE FOLLOWING PARAMETERS WILL BE MODIFIED.
 * 			Input read in the function will be stored in these parameters &
 * 			returned via the parameters.
 * 				input		: user input for an integer
 * ----------------------------------------------------------------------------
 * Returns nothing; alters the value of input
 *****************************************************************************/
void getAndValidateMenuInput(int& input,
							 const int LOWER_BOUND,
							 const int UPPER_BOUND)
{
	bool invalid = true;

	do
	{
		cout << "Enter selection: ";
		cin >> input;
		cin.ignore(10000, '\n');

		if (input < LOWER_BOUND || input > UPPER_BOUND)
		{
			cout << "Invalid entry. Try again.\n";
		}
		else
		{
			invalid = false;
		}
	} while (invalid);
}
