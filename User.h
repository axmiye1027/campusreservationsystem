#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class User
{
private:
  string username;
public:
  User();
  User(string userName);
  bool isUser(istream& file, string userName);
  bool isAdmin(istream&file, string userName);

  string getUsername();
  void setUsername(string userName);

  // The Load and Save functions for User Class
  bool saveToFile (const string& path) const;
  bool loadFromFile (const string& path);
};

#endif
