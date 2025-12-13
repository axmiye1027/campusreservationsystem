#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

using namespace std;

class Resource {
protected:
    int id;
    string name;

public:
    Resource(int id, const string& name);
    virtual ~Resource() = default;

    int getId() const;
    const string& getName() const;

     void setName(const string& newName);

    virtual void display(ostream& out) const = 0;
    virtual string getCategory() const = 0;

    virtual bool matchesAttribute(const string& attribute, const string& attributeValue) const = 0;

    friend ostream& operator<<(ostream& os, const Resource& r);
};


#endif
