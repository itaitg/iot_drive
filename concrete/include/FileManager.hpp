
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_FILEMANAGER_HPP
#define  ILRD_RD1645_FILEMANAGER_HPP

#include <fstream>

#include "IFileManager.hpp"
#include "Handleton.hpp"

namespace ilrd
{

class FileManager final : public IFileManager
{
public:
    friend class Handleton;
    ~FileManager() override = default;

    bool Read(const size_t offset_, const size_t length_,
        char* buffer_) override;
    bool Write(const size_t offset_, const size_t length_,
        const char* buffer_) override;

    FileManager(const FileManager& other_) = delete;
    FileManager& operator=(const FileManager& other_) = delete;
    FileManager(FileManager&& other_) = delete;
    FileManager& operator=(FileManager&& other_) = delete;
private:
    FileManager();
    std::fstream m_file;
    std::mutex m_mutex;

};
}

#endif // ILRD_RD1645_FILEMANAGER_HPP
