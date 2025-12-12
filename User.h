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
  bool isUser(istream& file, string userName);
  bool isAdmin(istream&file, string userName);

  string getUsername();
  void setUsername(string userName);
};
