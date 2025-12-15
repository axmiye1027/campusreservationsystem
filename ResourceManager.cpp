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

    //Saves to a File
    bool ResourceManager::saveToFile(const sting& path) const {
        ofstream out(path);
        if(!out) return false;
        out << resources.size() << '\n';
        for (const auto& r : resources) { 
            r.saveToFile(out);
        }
        return true;
    }

    //Load from a file
    bool ResourceManager::loadFromFile(const string& path) {
        ifstream in(path);
        if (!in) return false
        
        size_t count;
        in >> count;
        in.ignore();

        resources.clear();
        for (size_t i = 0; i < count; ++i) {
            int id;
            string name;

            in >> id;
            in.ignore();
            getline(in, name);
        }
        return true;
    }
}
