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
    void addResource(shared_ptr<Resource> resource) {
        resources.push_back(move(resource));
    }

    // Remove a resource by ID if it exists.
    bool removeResource(int id) {
        auto it = remove_if(resources.begin(), resources.end(), [id](const auto& res) {
            return res->getId() == id;
        });
        bool removed = it != resources.end();
        resources.erase(it, resources.end());
        return removed;
    }

    // Locate a resource by ID.
    shared_ptr<Resource> findResource(int id) const {
        for (const auto& res : resources) {
            if (res->getId() == id) return res;
        }
        return nullptr;
    }

    // Return a copy of all resources for display or iteration.
    vector<shared_ptr<Resource>> listResources() const {
        return resources;
    }
};

#endif
