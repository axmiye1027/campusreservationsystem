#include "User.h"
#include "UserManager.h"
#include "Menu.h"
#include "ResourceManager.h"
#include "ReservationManager.h"
#include <iostream>

using namespace std;

int main() {
    const int BORDER_SIZE = 80;
	User currentUser;
	UserManager userManager;
	ResourceManager resourceManager;
	ReservationManager reservationManager;
	int lowerBound = 0;
	int upperBound;
	int option = -1;
	
	// Load data from files
	resourceManager.loadFromFile("resources.txt");
	reservationManager.loadFromFile("reservations.txt");

	/**************************************************************************
	 * PROCESSING - This loop prompts users to login, create an account, or
	 * 				interact with campus resources. Users must be logged in to
	 * 				interact with resources.
	 *************************************************************************/
    do
    {
        displayMenu(BORDER_SIZE, currentUser);

        //Determine upperBound
        if (!currentUser.getIsLoggedIn()) { upperBound = 3; }
        else if (currentUser.getRole() == "Admin") { upperBound = 7; }
        else { upperBound = 6; }

        getAndValidateMenuInput(option,lowerBound,upperBound);//lowerBound is always = 0.

        switch (option)
        {
        case 0:
        	 if (!currentUser.getIsLoggedIn())
        	 {
        		 // Save data before exiting
        		 resourceManager.saveToFile("resources.txt");
        		 reservationManager.saveToFile("reservations.txt");
        		 cout << "\nExiting program.\n";
        		 return 0;
        	 }
        	 else
        	 {
        		 // Save data before logging out
        		 resourceManager.saveToFile("resources.txt");
        		 reservationManager.saveToFile("reservations.txt");
        		 currentUser.setIsLoggedIn(false);
        		 cout << "\nLogged out " << currentUser.getUsername() << "!\n";
        	 }
            break;

        case 1:
        	if (!currentUser.getIsLoggedIn())
        	 {
        	      currentUser = userManager.createAccount(BORDER_SIZE);
        	  }
            else if (currentUser.getRole() == "Admin")
            {
            	findResources(BORDER_SIZE, resourceManager);
            }
            else
            {
            	reserveResource(BORDER_SIZE, resourceManager, reservationManager, currentUser);
            }
            break;

        case 2:

            if (!currentUser.getIsLoggedIn())
            {
            	userManager.login(BORDER_SIZE, currentUser);
            }
            else if (currentUser.getRole() == "Admin")
            {
            	viewResources(BORDER_SIZE, resourceManager);
            }
            else
            {
            	findResources(BORDER_SIZE, resourceManager);
            }
            break;
        case 3:
        	if (currentUser.getRole() == "Admin")
        	{
        		addResource(BORDER_SIZE, resourceManager);
        	}
        	else
        	{
        		viewResources(BORDER_SIZE, resourceManager);
        	}
        	break;
        case 4:
        	if (currentUser.getRole() == "Admin")
        	{
        		editResource(BORDER_SIZE, resourceManager);
        	}
        	else
        	{
        		viewMyReservations(BORDER_SIZE, reservationManager, currentUser);
        	}
        	break;
        case 5:
        	if (currentUser.getRole() == "Admin")
        	{
        		deleteResource(BORDER_SIZE, resourceManager, reservationManager);
        	}
        	else
        	{
        		cancelReservation(BORDER_SIZE, reservationManager, currentUser);
        	}
        	break;
        case 6:
        	if (currentUser.getRole() == "Admin")
        	{
        		runAllTests(BORDER_SIZE);
        	}
        	break;

        default:
            cout << "\nInvalid option.\n";
        }

    } while (option != 0);




    
    return 0;
}

