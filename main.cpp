#include "TestSuite.h"
#include "User.h"
#include "UserManager.h"
#include "Menu.h"

int main() {
    TestSuite::runAllTests();

    const int BORDER_SIZE = 80;
	User currentUser;
	UserManager userManager;
	int lowerBound = 0;
	int upperBound;
	int option = -1;

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
        else if (currentUser.getRole() == "Admin") { upperBound = 6; }
        else { upperBound = 4; }

        getAndValidateMenuInput(option,lowerBound,upperBound);//lowerBound is always = 0.

        switch (option)
        {
        case 0:
        	 if (!currentUser.getIsLoggedIn())
        	 {
        		 cout << "\nExiting program.\n";
        		 return 0;
        	 }
        	 else
        	 {
        		 currentUser.setIsLoggedIn(false);
        		 cout << "\nLogged out " << currentUser.getUsername() << "!";

        	 }
            break;

        case 1:
        	if (!currentUser.getIsLoggedIn())
        	 {
        	      currentUser = userManager.createAccount(BORDER_SIZE);
        	  }
            else if (currentUser.getRole() == "Admin")
            {
            	//FINDING RESOURCES
            }
            else
            {
            	//RESERVING RESOURCES
            }
            break;

        case 2:

            if (!currentUser.getIsLoggedIn())
            {
            	userManager.login(BORDER_SIZE, currentUser);
            }
            else if (currentUser.getRole() == "Admin")
            {
            	//VIEW RESOURCES

            }
            else
            {
            	//FINDING RESOURCES
            }
            break;
        case 3:
        	if (currentUser.getRole() == "Admin")
        	{
        		//ADD CAMPUS RESOURCES
        	}
        	else
        	{
        		//VIEW CAMPUS RESOURCES
        	}
        	break;
        case 4:
        	//EDIT CAMPUS RESOURCES
        	break;
        case 5:
        	//DELETE CAMPUS RESOURCES
        	break;

        default:
            cout << "\nInvalid option.\n";
        }

    } while (option != 0);




    
    return 0;
}

