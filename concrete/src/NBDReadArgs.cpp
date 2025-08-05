//
// Created by bender on 4/6/25.
// Approved by:

#include "NBDReadArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::NBDReadArgs::NBDReadArgs(const NBDArgs& args_): m_offset(args_.m_offset),
    m_length(args_.m_length){}

size_t ilrd::NBDReadArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::NBDReadArgs::GetLength() const
{
    return m_length;
}

int ilrd::NBDReadArgs::GetKey()
{
    return 0;
}
