//
// Created by bender on 4/6/25.
// Approved by:

#include "NBDWriteArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
///
ilrd::NBDWriteArgs::NBDWriteArgs(const NBDArgs& args_): m_offset(args_.m_offset),
    m_length(args_.m_length), m_buffer(args_.m_buffer){}

size_t ilrd::NBDWriteArgs::GetOffset() const
{
    return m_offset;
}

size_t ilrd::NBDWriteArgs::GetLength() const
{
    return m_length;
}

std::shared_ptr<const char[]> ilrd::NBDWriteArgs::GetBuffer() const
{
    return m_buffer;
}

int ilrd::NBDWriteArgs::GetKey()
{
    return 1;
}

