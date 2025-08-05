
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_IFILEMANAGER_HPP
#define  ILRD_RD1645_IFILEMANAGER_HPP

namespace ilrd
{

class IFileManager 
{
public:
    IFileManager() = default;
    virtual ~IFileManager() = default;

    virtual bool Read(const size_t offset_, const size_t length_,
        char* buffer_) = 0;
    virtual bool Write(const size_t offset_, const size_t length_,
        const char* buffer_) = 0;

    IFileManager(const IFileManager& other_) = delete;
    IFileManager& operator=(const IFileManager& other_) = delete;
    IFileManager(IFileManager&& other_) = delete;
    IFileManager& operator=(IFileManager&& other_) = delete;
};
}

#endif // ILRD_RD1645_IFILEMANAGER_HPP
