//
// Created by bender on 4/7/25.
// Approved by:

#include "ATaskArgs.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::UID& ilrd::ATaskArgs::GetUID()
{
    return m_uid;
}

void ilrd::ATaskArgs::SetUID(const UID id_)
{
    m_uid = id_;
}
