//
// Created by bender on 4/20/25.
// Approved by:

#include "MinionReadArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::MinionReadArgs::MinionReadArgs(const MinionArgs& args_): m_offset(args_.m_offset),
    m_length(args_.m_length)
{
    SetUID(args_.m_id);
}


size_t ilrd::MinionReadArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::MinionReadArgs::GetLength() const
{
    return m_length;
}

int ilrd::MinionReadArgs::GetKey()
{
    return 0;
}
