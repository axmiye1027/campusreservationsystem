#include "StudyRoom.h"

// Constructor
StudyRoom::StudyRoom(int id,const string& name, int capacity,const string& location,const string& availabilityHours) : Resource(id, name),
    capacity(capacity), location(location), availabilityHours(availabilityHours) {
}

// Getters
int StudyRoom::getCapacity() const 
{ return capacity; }
const string& StudyRoom::getLocation() const
{ return location; }
const string& StudyRoom::getAvailabilityHours() const
{ return availabilityHours; }

// Setters
void StudyRoom::setCapacity(int cap)
{ capacity = cap; }
void StudyRoom::setLocation(const string& loc) 
{ location = loc; }
void StudyRoom::setAvailabilityHours(const string& hours)
{ availabilityHours = hours; }

// Overrides
string StudyRoom::getCategory() const {
    return "StudyRoom";
}

void StudyRoom::display(ostream& os) const {
    os << "[Study Room]\n"
        << "  ID: " << id << "\n"
        << "  Name: " << name << "\n"
        << "  Capacity: " << capacity << "\n"
        << "  Location: " << location << "\n"
        << "  Availability: " << availabilityHours << "\n";
}
