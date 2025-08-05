//
// Created by bender on 4/10/25.
// Approved by:

#include "AMessageResponse.hpp"

//////////////////include

//////////////////static declarations

//////////////////constructors

//////////////////static implementations
ilrd::AMessageResponse::AMessageResponse(const bool status_, const UID& id_):
    AMessage(id_), m_status(status_)
{}

char* ilrd::AMessageResponse::ToBuffer(char* buffer_)
{
    buffer_ = AMessage::ToBuffer(buffer_);

    *reinterpret_cast<bool*>(buffer_) = m_status;
    buffer_ += sizeof(bool);
    return buffer_;
}

char* ilrd::AMessageResponse::FromBuffer(char* buffer_)
{
    buffer_ = AMessage::FromBuffer(buffer_);
    m_status = *reinterpret_cast<bool*>(buffer_);
    buffer_ += sizeof(bool);

    return buffer_;
}

uint32_t ilrd::AMessageResponse::GetSize()
{
    return AMessage::GetSize() + sizeof(m_status);
}

bool ilrd::AMessageResponse::GetStatus()
{
    return m_status;
}
