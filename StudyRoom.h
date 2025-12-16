#ifndef STUDYROOM_H
#define STUDYROOM_H

#include "Resource.h"

class StudyRoom : public Resource {
private:
    //Attribute unique to Study room resource
    int capacity;
    string location;
    string availabilityHours;

public:
    StudyRoom(int id, const string& name, int capacity, const string& location, const string& availabilityHours);

    // Getters
    int getCapacity() const;
    const string& getLocation() const;
    const string& getAvailabilityHours() const;

    // Setters
    void setCapacity(int cap);
    void setLocation(const string& loc);
    void setAvailabilityHours(const string& hours);

    // Overrides
    string getCategory() const override;
    void display(ostream& os = cout) const override;
    bool matchesAttribute(const string& attribute, const string& attributeValue) const override;
};

#endif
