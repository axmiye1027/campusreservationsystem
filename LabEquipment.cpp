#include "LabEquipment.h"

// Constructor
LabEquipment::LabEquipment(int id,const string& name,const string& equipmentType, bool fragile): Resource(id, name),
    equipmentType(equipmentType), fragile(fragile) {
}

// Getters
const string& LabEquipment::getEquipmentType() const { return equipmentType; }
bool LabEquipment::isFragile() const { return fragile; }

// Setters
void LabEquipment::setEquipmentType(const string& type) { equipmentType = type; }
void LabEquipment::setFragile(bool f) { fragile = f; }

// Overrides
std::string LabEquipment::getCategory() const {
    return "LabEquipment";
}

void LabEquipment::display(ostream& os) const {
    os << "[Lab Equipment]\n"
        << "  ID: " << id << "\n"
        << "  Name: " << name << "\n"
        << "  Type: " << equipmentType << "\n"
        << "  Fragile: " << (fragile ? "Yes" : "No") << "\n";
}

bool LabEquipment::matchesAttribute(const string& attribute, const string& attributeValue) const
{
    if(attribute == "equipmentType")
    {
        return equipmentType == attributeValue;
    }

    if(attribute == "fragile")
    {
        bool fragility = (attributeValue == "true");
        return fragile == fragility;
    }

    return false;
}
