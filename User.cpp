#include "User.h"
#include "UserManager.h"

User::User()
{
	role = "Student";
	isLoggedIn = false;

	//PROC - To create a default username, we need to know what the last username was.
	ifstream fin;
	string lastUsername; //the last default username created, gives access to the last number used
	string lastNumber;//the number used in lastUsername, to be incremented to create a new default username
	fin.open("used_default_usernames.txt");

	if (!fin || !(fin >> lastUsername)) //if file does not exist/cannot open OR the file is empty
	{
		lastNumber = "0";
	}
	else
	{
		//if there are usernames, we want to keep reading until we hit the end;
		while (fin >> lastUsername) //reads a username only if the read succeeds
		{
		} //automatically traverses through the file
		lastNumber = lastUsername.substr(4);
	}

	fin.close();
	username = "User" + lastNumber;

}

User::User(string userName, string userRole)
{
	role = userRole;
	isLoggedIn = false;
	username = userName;
}


string User::getUsername()
{
  return username;
}

string User::getRole()
{
	return role;
}
bool User::getIsLoggedIn()
{
	return isLoggedIn;
}



void User::setUsername(string userName)
{
	username = userName;
}

void User::setRole(string role)
{
	this->role = role;
}

void User::setIsLoggedIn(bool isLoggedIn)
{
	this->isLoggedIn = isLoggedIn;
}





