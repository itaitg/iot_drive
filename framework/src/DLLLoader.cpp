//
// Created by bender on 3/19/25.
// Approved by:


#include "DLLLoader.hpp"

#include <dlfcn.h>
#include <stdexcept>

//////////////////include

//////////////////static declarations

//////////////////constructors

ilrd::DLLLoader::~DLLLoader()
{
    for(auto& m_plugin : m_plugins)
    {
        dlclose(m_plugin.second);
    }
}

//////////////////static implementations
void ilrd::DLLLoader::Load(const std::string& filename_)
{
    const handle handler = dlopen(filename_.c_str(), RTLD_LAZY);
    if(!handler)
    {
        throw std::runtime_error("dlopen");
    }
        m_plugins[filename_] = handler;
}

void ilrd::DLLLoader::Unload(const std::string& filename_)
{
    if(m_plugins.contains(filename_))
    {
        dlclose(m_plugins.at(filename_));
        m_plugins.erase(filename_);
    }
}

void ilrd::DLLLoader::Reload(const std::string& filename_)
{
    Unload(filename_);
    Load(filename_);
}