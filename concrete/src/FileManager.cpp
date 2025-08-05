//
// Created by bender on 4/20/25.
// Approved by:

#include "FileManager.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::FileManager::FileManager(): m_file("a.data")
{}

bool ilrd::FileManager::Read(const size_t offset_, const size_t length_,
        char* buffer_)
{
        std::unique_lock lock(m_mutex);
        m_file.seekg(offset_);
        m_file.read(buffer_, length_);

        return m_file.good();
}

bool ilrd::FileManager::Write(const size_t offset_, const size_t length_,
        const char* buffer_)
{
        std::unique_lock lock(m_mutex);
        m_file.seekp(offset_);
        m_file.write(buffer_, length_);
        m_file.flush();

        return m_file.good();
}
