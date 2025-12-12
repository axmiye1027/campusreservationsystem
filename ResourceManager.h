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

#endif
