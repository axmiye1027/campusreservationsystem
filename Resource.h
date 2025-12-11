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
    Resource(int id, string name) : id(id), name(move(name)) {}
    virtual ~Resource() = default;

    int getId() const { return id; }
    const string& getName() const { return name; }

    virtual void display(ostream& out) const = 0;
};

class StudyRoom : public Resource {
    int capacity;
    string location;
    string hours;

public:
    // Study room with capacity, location, and operating hours attributes.
    StudyRoom(int id, string name, int capacity, string location, string hours)
        : Resource(id, move(name)), capacity(capacity), location(move(location)), hours(move(hours)) {}

    void display(ostream& out) const override {
        out << "Study Room [ID " << id << "] " << name
            << " | Capacity: " << capacity
            << " | Location: " << location
            << " | Hours: " << hours;
    }
};

class LabEquipment : public Resource {
    string type;

public:
    // Lab equipment tagged by a descriptive type.
    LabEquipment(int id, string name, string type)
        : Resource(id, move(name)), type(move(type)) {}

    void display(ostream& out) const override {
        out << "Lab Equipment [ID " << id << "] " << name
            << " | Type: " << type;
    }
};

#endif
