#include "Resource.h"

// Constructor
Resource::Resource(int id, const string& name)
    : id(id), name(name) {
}

// Getters
int Resource::getId() const
{ return id; }
const string& Resource::getName() const
{ return name; }

void Resource::setName(const string& newName) {
    name = newName;
}

// Operator overload
ostream& operator<<(ostream& os, const Resource& r) {
    r.display(os);
    return os;
}
