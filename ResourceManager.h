#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Resource.h"
#include <memory>
#include <optional>
#include <vector>
#include <algorithm>

using namespace std;

class ResourceManager {
    vector<shared_ptr<Resource>> resources;

public:
    // Store a new resource instance.
    void addResource(shared_ptr<Resource> resource);

    // Remove a resource by ID if it exists.
    bool removeResource(int id);

    // Locate a resource by ID.
    shared_ptr<Resource> findResource(int id) const;

    // Return a copy of all resources for display or iteration.
    vector<shared_ptr<Resource>> listResources() const;

    //Filter resources by category
    vector<shared_ptr<Resource>> filterByCategory(const string& category) const;

    //Filter resources by attributes and their value
    vector<shared_ptr<Resource>> filterByAttribute(const string& attribute, const string& attributeValue) const;

    //Finds resources with name included in the resource name
    vector<shared_ptr<Resource>> findByName(const string& name) const;

    //Loads and Saves from/to a file
    bool saveToFile (const string& path) const;
    bool loadFromFile (const string& path);
};

#endif
