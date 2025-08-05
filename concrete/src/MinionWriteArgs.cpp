//
// Created by bender on 4/20/25.
// Approved by:

#include "MinionWriteArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::MinionWriteArgs::MinionWriteArgs(const MinionArgs& args_): m_offset(args_.m_offset),
    m_length(args_.m_length), m_buffer(args_.m_buffer)
{
    SetUID(args_.m_id);
}


size_t ilrd::MinionWriteArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::MinionWriteArgs::GetLength() const
{
    return m_length;
}

std::shared_ptr<const char[]> ilrd::MinionWriteArgs::GetBuffer() const
{
    return m_buffer;
}

int ilrd::MinionWriteArgs::GetKey()
{
    return 1;
}
