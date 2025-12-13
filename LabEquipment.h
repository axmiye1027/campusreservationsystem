#ifndef LABEQUIPMENT_H
#define LABEQUIPMENT_H

#include "Resource.h"

class LabEquipment : public Resource {
private:
    string equipmentType;
    bool fragile;

public:
    LabEquipment(int id, const string& name, const string& equipmentType, bool fragile);

    // Getters
    const string& getEquipmentType() const;
    bool isFragile() const;

    // Setters
    void setEquipmentType(const string& type);
    void setFragile(bool f);

    // Overrides
    string getCategory() const override;
    void display(ostream& os = cout) const override;
    bool matchesAttribute(const string& attribute, const string& attributeValue) const override;
};

#endif
