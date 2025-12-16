#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

using namespace std;

//Abstract base class for a campus resource
class Resource {
protected:
    int id;
    string name;

public:
    Resource(int id, const string& name);
    virtual ~Resource() = default;

    //getters
    int getId() const;
    const string& getName() const;

    //setter
    void setName(const string& newName);

    //pure virtual functions to be implemented by derived classes
    virtual void display(ostream& out) const = 0;
    virtual string getCategory() const = 0;
    virtual bool matchesAttribute(const string& attribute, const string& attributeValue) const = 0;

    //Overload the << operator calls display method
    friend ostream& operator<<(ostream& os, const Resource& r);
};


#endif
