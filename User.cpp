#include "User.h"

// Default constructor
User::User() : username("") {}

// Parameterized constructor
User::User(string userName) : username(userName) {}

// Implementation of Saving to File 
bool User::saveToFile (const string& path) const {
ofstream out (path);
if (!out) return false;
out << username << '\n';
return true;
}

//Implementaion of Loading from File
bool User::loadToFile (const string& path) const {
ifstream in (path);
if (!in) return false;
getlin (in, username);
return true;
}

// Getter
string User::getUsername()
{
    return username;
}

// Setter
void User::setUsername(string userName)
{
    username = userName;
}
