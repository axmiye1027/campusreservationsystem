// #include "TestSuite.h"

// int main() {
//     TestSuite::runAllTests();
//     return 0;
// }

#include "User.h"
#include "Menu.h"

int main()
{
	const int BORDER_SIZE = 50;
	User user;
	int option;


	option = -1;

	while (option != 0)
	{
		displayMainMenu();
		getAndValidateMenuInput(option);

		switch(option)
		{
		case 0: break;
		case 1: createAccount(BORDER_SIZE, user); break;
		case 2:
			break;

		case 3: //Calls reservation functions
			break;

		getAndValidateMenuInput(option);

		}


	return 0;
	}
}

