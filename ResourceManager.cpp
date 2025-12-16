#include "ResourceManager.h"
#include "StudyRoom.h"
#include "LabEquipment.h"
#include <algorithm>
#include <fstream>
#include <sstream>

// Store a new resource instance.
bool ResourceManager::addResource(shared_ptr<Resource> resource)
{
    // Check for duplicate ID
    if (findResource(resource->getId()) != nullptr) {
        return false;  // duplicate ID
    }

    resources.push_back(move(resource));
    return true;
}

// Remove a resource by ID if it exists.
bool ResourceManager::removeResource(int id) {
    auto it = remove_if(resources.begin(), resources.end(),
                        [id](const auto& res) {
                            return res->getId() == id;
                        });

    bool removed = (it != resources.end());
    resources.erase(it, resources.end());
    return removed;
}

// Locate a resource by ID.
shared_ptr<Resource> ResourceManager::findResource(int id) const {
    for (const auto& res : resources) {
        if (res->getId() == id)
            return res;
    }
    return nullptr;
}

// Return a copy of all resources for display or iteration.
vector<shared_ptr<Resource>> ResourceManager::listResources() const {
    return resources;
}

//Filter resources by category
vector<shared_ptr<Resource>> ResourceManager::filterByCategory(const string& category) const
{
    vector<shared_ptr<Resource>> result;

    for(const auto& res : resources)
    {
        if(res->getCategory() == category)
        {
            result.push_back(res);
        }
    }

    return result;
}

//Filter resources by attribute and value
vector<shared_ptr<Resource>> ResourceManager::filterByAttribute(const string& attribute, const string& attributeValue) const
{
    vector<shared_ptr<Resource>> result;

    for(const auto& res : resources)
    {
        if(res->matchesAttribute(attribute, attributeValue))
        {
            result.push_back(res);
        }
    }

    return result;
}


//Returns a vector of resources with the key name included in the resource name
vector<shared_ptr<Resource>> ResourceManager::findByName(const string& name) const
{
    vector<shared_ptr<Resource>> result;

    for(const auto& res : resources)
    {
        if(res->getName().find(name) != string::npos)
        {
            result.push_back(res);
        }
    }

    return result;
}

// Save resources to file
bool ResourceManager::saveToFile(const string& path) const {
    ofstream out(path);
    if (!out.is_open()) return false;

    for (const auto& res : resources) {
        string category = res->getCategory();
        if (category == "StudyRoom") {
            auto studyRoom = dynamic_pointer_cast<StudyRoom>(res);
            if (studyRoom) {
                out << "StudyRoom," << studyRoom->getId() << "," << studyRoom->getName() << ","
                    << studyRoom->getCapacity() << "," << studyRoom->getLocation() << ","
                    << studyRoom->getAvailabilityHours() << "\n";
            }
        } else if (category == "LabEquipment") {
            auto labEquipment = dynamic_pointer_cast<LabEquipment>(res);
            if (labEquipment) {
                out << "LabEquipment," << labEquipment->getId() << "," << labEquipment->getName() << ","
                    << labEquipment->getEquipmentType() << "," << (labEquipment->isFragile() ? "true" : "false") << "\n";
            }
        }
    }
    return true;
}

// Load resources from file
bool ResourceManager::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in.is_open()) {
        return false;
    }

    resources.clear();

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 3) continue;

        string type = tokens[0];
        int id = stoi(tokens[1]);
        string name = tokens[2];

        if (type == "StudyRoom" && tokens.size() >= 6) {
            int capacity = stoi(tokens[3]);
            string location = tokens[4];
            string availabilityHours = tokens[5];
            auto studyRoom = make_shared<StudyRoom>(id, name, capacity, location, availabilityHours);
            resources.push_back(studyRoom);
        } else if (type == "LabEquipment" && tokens.size() >= 5) {
            string equipmentType = tokens[3];
            bool fragile = (tokens[4] == "true");
            auto labEquipment = make_shared<LabEquipment>(id, name, equipmentType, fragile);
            resources.push_back(labEquipment);
        }
    }
    return true;
}
