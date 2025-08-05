
//
// Created by bender on 3/19/25.
#ifndef  ILRD_RD1645_DLLLOADER_HPP
#define  ILRD_RD1645_DLLLOADER_HPP

#include <string>
#include <unordered_map>


namespace ilrd
{
///Loads DLLs for directory (to be used with @DirMonitor)
class DLLLoader 
{
public:
    DLLLoader() = default;
    ~DLLLoader();
    DLLLoader(const DLLLoader& other_) = delete;
    DLLLoader& operator=(const DLLLoader& other_) = delete;
    DLLLoader(DLLLoader&& other_) = delete;
    DLLLoader& operator=(DLLLoader&& other_) = delete;

    ///Loads DLL
    void Load(const std::string& filename_);
    ///Unloads DLL
    void Unload(const std::string& filename_);
    ///Updates DLL
    void Reload(const std::string& filename_);
private:
    typedef void* handle;
    std::unordered_map<std::string, handle> m_plugins;

};
}

#endif // ILRD_RD1645_DLLLOADER_HPP
