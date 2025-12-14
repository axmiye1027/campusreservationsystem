#include "User.h"

// Default constructor
User::User() : username("") {}

// Parameterized constructor
User::User(string userName) : username(userName) {}







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
