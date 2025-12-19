/******************************************************************************
 * AUTHORS			: Paul S, Ryland L, Amy X, Cristal D, Elizabeth S
 * PROJECT #3		: Campus Reservation System
 * CLASS			: CS 1C
 * SECTION			: TTh 8a
 * DUE DATE			: 12/22/25
******************************************************************************/
#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include "User.h"
#include "ResourceManager.h"
#include "ReservationManager.h"
using namespace std;

/***********************************************************************
 * FUNCTION - displayMenu
 * ---------------------------------------------------------------------
 * Displays a menu for users. The menu displayed depends on whether the user
 * is logged in and if they are a student or admin.
 *
 * EXAMPLE OUTPUT (console):
 *
 * 		===============================================================
 * 		SMART CAMPUS RESERVATION SYSTEM
 * 		---------------------------------------------------------------
 *		What would you like to do today?
 * 		0. Exit program
 * 		1. Create an account
 * 		2. Login to your account
 * 		===============================================================
 *
 * 		===============================================================
 * 		SMART CAMPUS RESERVATION SYSTEM | Student: janeDoe
 * 		---------------------------------------------------------------
 *		What would you like to do today?
 * 		0. Exit program
 * 		1. Reserve campus resources
 * 		2. Find campus resources
 * 		3. View campus resources
 * 		===============================================================
 *
 * 		===============================================================
 * 		SMART CAMPUS RESERVATION SYSTEM | Admin: johnDoe
 * 		---------------------------------------------------------------
 *		What would you like to do today?
 * 		0. Exit program
 * 		1. Find campus resources
 * 		2. View campus resources
 * 		3. Add campus resources
 * 		4. Edit campus resources
 * 		5. Delete campus resources
 * 		===============================================================
 *
 * ---------------------------------------------------------------------
 * Returns nothing; outputs main menu.
 **********************************************************************/
void displayMenu(const int BORDER_SIZE, User &u);

/***********************************************************************
 * FUNCTION - getAndValidateMenuInput
 * ---------------------------------------------------------------------
 * Receives initial user input and checks if it within the valid range
 * specified by LOWER_BOUND and UPPER_BOUND.
 *
 * ---------------------------------------------------------------------
 * Returns nothing; alters the value of input
 **********************************************************************/
void getAndValidateMenuInput(int& input, const int LOWER_BOUND, const int UPPER_BOUND);

// Student menu functions
void reserveResource(const int BORDER_SIZE, ResourceManager& resourceManager, 
                     ReservationManager& reservationManager, User& currentUser);
void findResources(const int BORDER_SIZE, ResourceManager& resourceManager);
void viewResources(const int BORDER_SIZE, ResourceManager& resourceManager);
void viewMyReservations(const int BORDER_SIZE, ReservationManager& reservationManager, 
                        User& currentUser);
void cancelReservation(const int BORDER_SIZE, ReservationManager& reservationManager, 
                       User& currentUser);

// Admin menu functions
void addResource(const int BORDER_SIZE, ResourceManager& resourceManager);
void editResource(const int BORDER_SIZE, ResourceManager& resourceManager);
void deleteResource(const int BORDER_SIZE, ResourceManager& resourceManager, 
                    ReservationManager& reservationManager);
void runAllTests(const int BORDER_SIZE);

#endif
