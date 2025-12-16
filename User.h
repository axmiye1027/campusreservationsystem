#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class User
{
private:
  string username;
  string role;
  bool isLoggedIn;

public:
  User();
  User(string userName, string userRole);

  /***********************************************************************
   * FUNCTION - login
   * ---------------------------------------------------------------------
   * Provides an interface for the user to login. Outputs a message that
   * says whether login was successful or not.
   *
   * EXAMPLE OUTPUT (console):
   * 	==================================================================
   * 	LOGIN
   * 	------------------------------------------------------------------
   * 	Enter username: JohnDoe123
   * 	Login successful!
   * 	==================================================================
   *
   * ---------------------------------------------------------------------
   * Returns nothing, outputs login interface and validates user.
   **********************************************************************/
  void login(string userName);

  string getUsername();
  string getRole();
  bool getIsLoggedIn();

  void setUsername(string userName);
  void setRole(string role);
  void setIsLoggedIn(bool isLoggedIn);

};

/***********************************************************************
 * FUNCTION - validateUsername
 * ---------------------------------------------------------------------
 * Takes a user's role and username and searches through the respective
 * file. Prompts for a new username until a unique username is chosen.
 * ---------------------------------------------------------------------
 * Returns a string representing the unique username chosen by the user.
 **********************************************************************/
string validateUsername(string userName, string role);


void addUserToFile(ostream& outFile, User& u);


#endif
