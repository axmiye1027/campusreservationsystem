/******************************************************************************
 * AUTHORS			: Paul S, Ryland L, Amy X, Cristal D, Elizabeth S
 * PROJECT #3		: Campus Reservation System
 * CLASS			: CS 1C
 * SECTION			: TTh 8a
 * DUE DATE			: 12/22/25
******************************************************************************/
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


  void login(string userName);

  string getUsername();
  string getRole();
  bool getIsLoggedIn();

  void setUsername(string userName);
  void setRole(string role);
  void setIsLoggedIn(bool isLoggedIn);


};




#endif
