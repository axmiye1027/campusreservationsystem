#include "ResourceManager.h"
#include <algorithm>

// Store a new resource instance.
void ResourceManager::addResource(shared_ptr<Resource> resource) {
    resources.push_back(move(resource));
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
